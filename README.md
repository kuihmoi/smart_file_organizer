# Smart File Organizer Agent 📂🤖

An automated, asynchronous background utility designed to manage local directory clutter by monitoring file system modification events, detecting storage redundancy, and dynamically routing files to semantic subfolders.

This project was built as part of the **Operating Systems** curriculum at Sejong University.

---

## 💡 The Real-World Problem
In modern operating systems, high-traffic user directories (like `Downloads` or `Desktop`) quickly become chaotic storage dumps. This digital clutter leads to navigation delays, fragmentation of user workflow, and inefficient disk utilization due to undetected duplicate files. 

**The Solution:** An autonomous background agent that abstracts file management from the user by responding to live file creation hooks, processing file attributes, and handling atomic I/O storage transfers instantly.

---

## 🛠️ System Architecture & Perception-Action Loop

The system operates on an event-driven loop that bridges user activity to low-level kernel APIs:

```text
[ User Drops File ] ────► [ Watchdog Listener ] ────► [ File System Events (Inotify/FSEvents) ]
                                                                      │
                                                                      ▼
[ Action Log ] ◄──── [ File Mover Engine ] ◄──── [ MD5 Duplicate & Extension Classifier ]
```

---

## 🚀 Getting Started

### 1. Environment Setup
Clone the repository and set up a virtual environment to manage dependencies securely:

```bash
git clone [https://github.com/kuihmoi/smart_file_organizer.git](https://github.com/kuihmoi/smart_file_organizer.git)
cd smart_file_organizer

# Windows
python -m venv venv
.\venv\Scripts\activate

# macOS / Linux
python3 -m venv venv
source venv/bin/activate
```

### 2. Install Dependencies
```bash
pip install -r requirements.txt
```

---

## ⚙️ How to Operate

### 1. Configuration Setup
The agent reads operational rules from `config/settings.yaml`. Adjust your target directory paths and active flags here:

```yaml
source_directory: "~/Downloads"
destination_root: "~/Organized_Files"
deduplication: true
deep_scan: false
exclude_folders: [".git", "node_modules", ".venv"]
```

### 2. Execution
Launch the utility to initiate the background observer or trigger an instant directory scan:

```bash
python src/main.py
```

### 3. Dry-Run Verification (Safe Mode)
To simulate the agent's structural mutations and preview organizing outcomes without actually modifying your underlying disk partition, append the `--dry-run` flag:

```bash
python src/main.py --source ~/Desktop --dest ~/Desktop/Archived --dry-run
```

---

## 📄 License

This project is open-source software licensed under the [MIT License](LICENSE).