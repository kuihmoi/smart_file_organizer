import os

# The folder the agent will watch
WATCH_FOLDER = os.path.join(os.path.dirname(__file__), "watched_folder")

# Rules: file extension → subfolder name
FILE_CATEGORIES = {
    # Images
    ".jpg": "Images",
    ".jpeg": "Images",
    ".png": "Images",
    ".gif": "Images",
    ".svg": "Images",
    ".webp": "Images",

    # Documents
    ".pdf": "Documents",
    ".docx": "Documents",
    ".doc": "Documents",
    ".txt": "Documents",
    ".pptx": "Documents",
    ".xlsx": "Documents",

    # Code
    ".py": "Code",
    ".js": "Code",
    ".html": "Code",
    ".css": "Code",
    ".cpp": "Code",
    ".java": "Code",
    ".c": "Code",

    # Video
    ".mp4": "Videos",
    ".mov": "Videos",
    ".avi": "Videos",

    # Audio
    ".mp3": "Audio",
    ".wav": "Audio",

    # Archives
    ".zip": "Archives",
    ".rar": "Archives",
    ".7z": "Archives",
}

# If file type is unknown, put it here
DEFAULT_CATEGORY = "Others"