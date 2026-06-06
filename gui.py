import tkinter as tk
from tkinter import ttk, scrolledtext
import threading
import time
import os
from datetime import datetime
from watchdog.observers import Observer
from file_mover import move_file
from watchdog.events import FileSystemEventHandler
from config import WATCH_FOLDER


class FileOrganizerGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Smart File Organizer Agent")
        self.root.geometry("700x600")
        self.root.configure(bg="#f5f5f5")
        self.observer = None
        self.running = False
        self.stats = {"moved": 0, "skipped": 0, "errors": 0}

        self.build_ui()

    def build_ui(self):
        # ── Title bar ──
        title_frame = tk.Frame(self.root, bg="#1e1e2e", pady=12)
        title_frame.pack(fill="x")
        tk.Label(title_frame, text="Smart File Organizer Agent",
                 bg="#1e1e2e", fg="white",
                 font=("Segoe UI", 14, "bold")).pack()

        # ── Status bar ──
        self.status_frame = tk.Frame(self.root, bg="#e8f5e9", pady=8)
        self.status_frame.pack(fill="x", padx=16, pady=(12, 0))
        self.status_dot = tk.Label(self.status_frame, text="●",
                                   bg="#e8f5e9", fg="#388e3c",
                                   font=("Segoe UI", 10))
        self.status_dot.pack(side="left", padx=(12, 4))
        self.status_label = tk.Label(self.status_frame,
                                     text="Agent stopped",
                                     bg="#e8f5e9", fg="#388e3c",
                                     font=("Segoe UI", 10))
        self.status_label.pack(side="left")

        # ── Watched folder path ──
        folder_frame = tk.Frame(self.root, bg="#f5f5f5")
        folder_frame.pack(fill="x", padx=16, pady=(10, 0))
        tk.Label(folder_frame, text="Watching:",
                 bg="#f5f5f5", fg="#666",
                 font=("Segoe UI", 9)).pack(side="left")
        tk.Label(folder_frame, text=WATCH_FOLDER,
                 bg="#f5f5f5", fg="#333",
                 font=("Segoe UI", 9, "bold")).pack(side="left", padx=6)

        # ── Stats cards ──
        stats_frame = tk.Frame(self.root, bg="#f5f5f5")
        stats_frame.pack(fill="x", padx=16, pady=12)

        self.moved_label = self.make_stat_card(stats_frame, "Moved", "0", "#1565c0")
        self.skipped_label = self.make_stat_card(stats_frame, "Skipped", "0", "#e65100")
        self.errors_label = self.make_stat_card(stats_frame, "Errors", "0", "#c62828")

        # ── Live log ──
        tk.Label(self.root, text="LIVE ACTIVITY LOG",
                 bg="#f5f5f5", fg="#999",
                 font=("Segoe UI", 8)).pack(anchor="w", padx=16)

        self.log_box = scrolledtext.ScrolledText(
            self.root, height=14, font=("Consolas", 9),
            bg="#1e1e2e", fg="#cdd6f4",
            insertbackground="white", relief="flat",
            padx=10, pady=10
        )
        self.log_box.pack(fill="both", expand=True, padx=16, pady=(4, 0))
        self.log_box.config(state="disabled")

        # ── Buttons ──
        btn_frame = tk.Frame(self.root, bg="#f5f5f5")
        btn_frame.pack(pady=12)

        self.start_btn = tk.Button(
            btn_frame, text="▶  Start Agent",
            command=self.start_agent,
            bg="#1565c0", fg="white",
            font=("Segoe UI", 10, "bold"),
            padx=16, pady=6, relief="flat", cursor="hand2"
        )
        self.start_btn.pack(side="left", padx=6)

        self.stop_btn = tk.Button(
            btn_frame, text="■  Stop Agent",
            command=self.stop_agent,
            bg="#c62828", fg="white",
            font=("Segoe UI", 10, "bold"),
            padx=16, pady=6, relief="flat", cursor="hand2",
            state="disabled"
        )
        self.stop_btn.pack(side="left", padx=6)

        tk.Button(
            btn_frame, text="Clear Log",
            command=self.clear_log,
            bg="#eeeeee", fg="#333",
            font=("Segoe UI", 10),
            padx=16, pady=6, relief="flat", cursor="hand2"
        ).pack(side="left", padx=6)

    def make_stat_card(self, parent, label, value, color):
        card = tk.Frame(parent, bg="white", padx=20, pady=10,
                        relief="flat", bd=1)
        card.pack(side="left", padx=6, fill="x", expand=True)
        tk.Label(card, text=label, bg="white", fg="#999",
                 font=("Segoe UI", 9)).pack()
        val_label = tk.Label(card, text=value, bg="white", fg=color,
                             font=("Segoe UI", 20, "bold"))
        val_label.pack()
        return val_label

    def log(self, message, tag="info"):
        colors = {"moved": "#a6e3a1", "skipped": "#f9e2af",
                  "error": "#f38ba8", "info": "#cdd6f4"}
        color = colors.get(tag, "#cdd6f4")
        timestamp = datetime.now().strftime("%H:%M:%S")
        self.log_box.config(state="normal")
        self.log_box.insert("end", f"[{timestamp}] {message}\n", tag)
        self.log_box.tag_config(tag, foreground=color)
        self.log_box.see("end")
        self.log_box.config(state="disabled")

    def clear_log(self):
        self.log_box.config(state="normal")
        self.log_box.delete("1.0", "end")
        self.log_box.config(state="disabled")

    def update_stats(self):
        self.moved_label.config(text=str(self.stats["moved"]))
        self.skipped_label.config(text=str(self.stats["skipped"]))
        self.errors_label.config(text=str(self.stats["errors"]))

    def set_status(self, running: bool):
        if running:
            self.status_frame.config(bg="#e8f5e9")
            self.status_dot.config(bg="#e8f5e9", fg="#388e3c")
            self.status_label.config(bg="#e8f5e9", fg="#388e3c",
                                     text="Agent running — watching for new files")
            self.start_btn.config(state="disabled")
            self.stop_btn.config(state="normal")
        else:
            self.status_frame.config(bg="#fce4ec")
            self.status_dot.config(bg="#fce4ec", fg="#c62828")
            self.status_label.config(bg="#fce4ec", fg="#c62828",
                                     text="Agent stopped")
            self.start_btn.config(state="normal")
            self.stop_btn.config(state="disabled")

    def start_agent(self):
        self.running = True
        self.set_status(True)
        self.log("Agent started. Watching: " + WATCH_FOLDER, "info")

        gui_ref = self

        class GUIHandler(FileSystemEventHandler):
            def on_created(self, event):
                if event.is_directory:
                    return
                file_path = event.src_path
                gui_ref.log(f"Detected: {os.path.basename(file_path)}", "info")
                time.sleep(1)
                try:
                    move_file(file_path)
                    gui_ref.stats["moved"] += 1
                    gui_ref.log(f"MOVED: {os.path.basename(file_path)}", "moved")
                except Exception as e:
                    gui_ref.stats["errors"] += 1
                    gui_ref.log(f"ERROR: {str(e)}", "error")
                gui_ref.root.after(0, gui_ref.update_stats)

        def run_observer():
            self.observer = Observer()
            self.observer.schedule(GUIHandler(), WATCH_FOLDER, recursive=False)
            self.observer.start()
            while self.running:
                time.sleep(1)

        thread = threading.Thread(target=run_observer, daemon=True)
        thread.start()

    def stop_agent(self):
        self.running = False
        if self.observer:
            self.observer.stop()
            self.observer.join()
        self.set_status(False)
        self.log("Agent stopped.", "info")


if __name__ == "__main__":
    root = tk.Tk()
    app = FileOrganizerGUI(root)
    root.mainloop()