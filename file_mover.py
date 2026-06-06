import os
import shutil
from classifier import classify_file
from duplicate_checker import is_duplicate
from logger import log_action, log_error
from config import WATCH_FOLDER


def move_file(file_path: str):
    """
    The main decision-making function.
    Takes a file, decides where it goes, and moves it.
    """
    try:
        # Step 1: Check if file still exists (might have been moved already)
        if not os.path.exists(file_path):
            return

        # Step 2: Check for duplicates
        if is_duplicate(file_path):
            log_action("SKIPPED (duplicate)", file_path, status="SKIPPED")
            return

        # Step 3: Classify the file
        category = classify_file(file_path)

        # Step 4: Build the destination folder path
        destination_folder = os.path.join(WATCH_FOLDER, category)

        # Step 5: Create the folder if it doesn't exist yet
        os.makedirs(destination_folder, exist_ok=True)

        # Step 6: Build full destination path
        file_name = os.path.basename(file_path)
        destination_path = os.path.join(destination_folder, file_name)

        # Step 7: Handle name conflict (different file, same name)
        if os.path.exists(destination_path):
            name, ext = os.path.splitext(file_name)
            destination_path = os.path.join(destination_folder, f"{name}_renamed{ext}")

        # Step 8: Move the file
        shutil.move(file_path, destination_path)
        log_action("MOVED", file_path, destination_path)

    except Exception as e:
        log_error(f"Failed to move {file_path} | Error: {str(e)}")