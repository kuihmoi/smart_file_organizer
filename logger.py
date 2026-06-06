import logging
import os
from datetime import datetime

# Create a logs folder if it doesn't exist
LOG_FOLDER = os.path.join(os.path.dirname(__file__), "logs")
os.makedirs(LOG_FOLDER, exist_ok=True)

# Log file named with today's date
LOG_FILE = os.path.join(LOG_FOLDER, f"log_{datetime.now().strftime('%Y-%m-%d')}.txt")

# Set up the logger
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s | %(levelname)s | %(message)s",
    handlers=[
        logging.FileHandler(LOG_FILE),      # saves to file
        logging.StreamHandler()             # also prints to terminal
    ]
)

logger = logging.getLogger("FileOrganizerAgent")


def log_action(action: str, source: str, destination: str = "", status: str = "SUCCESS"):
    message = f"{action} | Source: {source} | Destination: {destination} | Status: {status}"
    logger.info(message)


def log_error(message: str):
    logger.error(message)