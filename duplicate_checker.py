import hashlib
import os

# This dictionary stores hashes of files we've already seen
# Key: hash value → Value: original file path
hash_registry = {}


def get_file_hash(file_path: str) -> str:
    """
    Reads a file and computes its MD5 hash.
    Two identical files will always produce the same hash.
    """
    hasher = hashlib.md5()

    with open(file_path, "rb") as f:
        # Read in chunks so large files don't crash memory
        chunk = f.read(8192)
        while chunk:
            hasher.update(chunk)
            chunk = f.read(8192)

    return hasher.hexdigest()


def is_duplicate(file_path: str) -> bool:
    """
    Returns True if we've seen this exact file before.
    Returns False if it's a new unique file.
    """
    file_hash = get_file_hash(file_path)

    if file_hash in hash_registry:
        return True
    else:
        # New file — register its hash
        hash_registry[file_hash] = file_path
        return False