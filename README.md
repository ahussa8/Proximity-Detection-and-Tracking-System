# ME 331 Midterm Project – Proximity, Detection, and Tracking System

**Author:** Abbas Hussain  
**Course:** ME 331 – Mechatronics  
**Semester:** Spring 2025

This project integrates multiple mechatronics subsystems using Arduino to sense, detect, and respond to nearby objects with real-time feedback. It consists of four major parts: Proximity Warning, Situational Awareness, Object Detection, and Optional Object Tracking.

---

## 🔧 Components Used

- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- SG90 Servo Motor
- RGB LED
- Buzzer
- Push Button
- Jumper Wires, Breadboard

---

## ⚙️ Part 1: Proximity Warning System

### 🎯 Objectives
- Average 5 distance readings using an ultrasonic sensor.
- Calculate object velocity.
- RGB LED status:
  - **Green:** Safe (distance > 10 cm)
  - **Yellow:** Stationary/receding within 10 cm
  - **Red + Buzzer:** Approaching within 10 cm
- Display status and distance on Serial Monitor.

### ✅ Outcome
- Accurately computed object velocity.
- Real-time visual and audio alerts based on motion.
- Serial Monitor output for debugging and verification.

---

## 🧭 Part 2: Situational Awareness

### 🎯 Objectives
- Rotate ultrasonic sensor via servo to 0°, 90°, 180°.
- Measure distance in each direction.
- Classify environment:
  - Open Space, Corridor, Dead End, Corners, Walls, etc.
- Display classification on Serial Monitor.

### ✅ Outcome
- Robust scanning and angle-based classification.
- Real-time environment awareness output.
- Accurate direction mapping using simple logic.

---

## 🛰️ Part 3: Object Detector

### 🎯 Objectives
- Triggered by button press.
- Scan from 0° to 180° in 5° steps.
- Find angle of closest object.
- Rotate servo to face it.
- RGB LED:
  - **Red:** Scanning
  - **Green:** Object Detected

### ✅ Outcome
- Seamless scanning and object tracking.
- Nearest object located and faced correctly.
- Clear visual feedback and Serial Monitor output.

---

## 🎯 Part 4 (Optional): Object Tracking System

### 🎯 Objectives
- Continuously scan for objects.
- Track object dynamically once detected.
- Return to scan mode if object is lost (>10 cm).
- Localized ±20° micro-scan for object refinement.
- RGB LED:
  - **Red:** Scanning
  - **Green:** Tracking

### ✅ Outcome
- Smooth transitions between scan and track modes.
- Accurate and responsive servo positioning.
- Efficient resource use via micro-scanning.

---

## 📈 Project Highlights

- 🧠 Real-time object classification and decision making.
- 🔄 Dynamic servo control with environmental context.
- 💡 RGB LED provides intuitive status feedback.
- 📢 Buzzer ensures audible proximity alerts.
- 🖥️ Serial Monitor shows all key values and statuses.

---

## 🛠️ Future Improvements

- Implement LCD output for visual feedback.
- Add IR sensor array for surface detection.
- Use motor control to drive an actual robot based on awareness data.

---

## 🎥 Deliverables

- `MidtermProject_AbbasHussain.ino` — Final sketch
- `midterm_demo_video.mp4` — Demonstration of all modules

---

> 🧪 *Tested under varied conditions for all edge cases, this system demonstrates fundamental sensor integration, control logic, and feedback mechanisms suitable for real-world autonomous applications.*
