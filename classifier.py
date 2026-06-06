import os
from config import FILE_CATEGORIES, DEFAULT_CATEGORY


def classify_file(file_path: str) -> str:
    """
    Takes a file path and returns the category name.
    Example: "photo.jpg" → "Images"
    """
    # Get the file extension and make it lowercase
    extension = os.path.splitext(file_path)[1].lower()

    # Look it up in our rules from config.py
    category = FILE_CATEGORIES.get(extension, DEFAULT_CATEGORY)

    return category