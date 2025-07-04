# Weed-Detection-and-Destruction-using-Laser

[![Language](https://img.shields.io/badge/Language-Python-yellow.svg?style=for-the-badge)](https://en.wikipedia.org/wiki/Programming_language)

This project addresses the challenge of weed management by developing a system capable of detecting weeds and potentially destroying them using a laser mechanism. Leveraging computer vision techniques, this system is designed for applications in precision agriculture and automated gardening.

---

## 📑 Table of Contents

- [Features](#features)
- [Technologies Used](#technologies-used)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)

---

## 🚀 Features

- **Automated Weed Detection:** Likely uses a trained YOLO model for identifying weeds in video or image frames.
- **Laser Targeting Integration:** Intended to connect with hardware (e.g., laser actuators) for precision weed elimination.
- **Calibration System:** Includes calibration scripts (under `calibration_code/`) for accurate targeting.
- **Dataset Handling:** Incorporates weed datasets for training or evaluation.
- **Video Input Support:** Supports video files like `vid1.mp4`, `vid2.mp4`, or live feeds for detection.

---

## 🧰 Technologies Used

- **Language:** Python
- **Libraries & Tools:**
  - absl-py
  - aiohttp, aiosignal
  - altair
  - annotated-types
  - anyio
  - numpy, opencv-python, matplotlib
  - PyYAML (likely used for `data.yaml`)
  - YOLO model-related dependencies
  - *(Full list available in `requirements.txt`)*

---

## ⚙️ Installation

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/your-username/weed-detection-and-destruction-using-laser.git
    cd weed-detection-and-destruction-using-laser
    ```

2. **Install Dependencies:**

    Make sure you have Python and pip installed. Then run:

    ```bash
    pip install -r requirements.txt
    ```

---

## ▶️ Usage

1. **(Optional) Configure Dataset & Calibration:**
   - Edit `data.yaml` as needed.
   - Run calibration routines from the `calibration_code/` directory if using a physical targeting system.

2. **Run the Application:**

    ```bash
    python app.py
    ```

    > Modify the script name if your main entry point differs (e.g., `frames.py`).

3. **Input Sources:**
   - You may be able to switch between live feed and video input (e.g., `vid1.mp4`, `vid2.mp4`).
   - Refer to internal code or arguments in `app.py` for usage options.

---

## 🤝 Contributing

We welcome your contributions!

1. Fork the repository
2. Create your feature branch:
    ```bash
    git checkout -b feature/AmazingFeature
    ```
3. Commit your changes:
    ```bash
    git commit -m "Add AmazingFeature"
    ```
4. Push to your branch:
    ```bash
    git push origin feature/AmazingFeature
    ```
5. Open a pull request

---
