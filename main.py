import time
import os
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
from file_mover import move_file
from logger import log_action, log_error
from config import WATCH_FOLDER
from rich.console import Console
from rich.panel import Panel

console = Console()


class FileOrganizerHandler(FileSystemEventHandler):
    """
    This class listens for file system events.
    When a new file appears, it triggers the agent.
    """

    def on_created(self, event):
        # Ignore folders, only handle files
        if event.is_directory:
            return

        file_path = event.src_path
        console.print(f"[bold cyan]📁 New file detected:[/bold cyan] {file_path}")

        # Small delay to make sure the file is fully written
        time.sleep(1)

        # Hand off to the file mover
        move_file(file_path)


def start_agent():
    # Make sure the watched folder exists
    os.makedirs(WATCH_FOLDER, exist_ok=True)

    console.print(Panel.fit(
        "[bold green]Smart File Organizer Agent[/bold green]\n"
        f"[white]Watching:[/white] [yellow]{WATCH_FOLDER}[/yellow]\n"
        "[white]Press[/white] [bold red]Ctrl+C[/bold red] [white]to stop[/white]",
        border_style="green"
    ))

    # Set up the watchdog observer
    event_handler = FileOrganizerHandler()
    observer = Observer()
    observer.schedule(event_handler, WATCH_FOLDER, recursive=False)
    observer.start()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        console.print("\n[bold red]Agent stopped.[/bold red]")
        observer.stop()

    observer.join()


if __name__ == "__main__":
    start_agent()