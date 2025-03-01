# 📡 IoT-Based Transformer Health Monitoring System 

## 🚀 Project Overview

The **IoT-Based Transformer Health Monitoring System** is designed to enhance transformer safety, efficiency, and reliability by continuously monitoring **temperature and load current . By integrating **IoT technology** with real-time sensors and automated control mechanisms, this system provides predictive maintenance insights and prevents transformer failures.  

## 🔥 Key Features  
✅ **Real-Time Monitoring:** Continuously tracks **temperature and current using integrated sensors.  
✅ **Automated Cooling System:**  
   - **70°C - 80°C →** Fan runs at **50% speed**  
   - **80°C - 90°C →** Fan runs at **100% speed**, Buzzer ON  
✅ **Overload Protection:** A **5V relay automatically disconnects the load** if temperature or current exceeds the threshold.  
✅ **IoT Connectivity:** Data is sent to the **Blynk IoT platform** for remote monitoring and real-time alerts.  
✅ **LCD Display:** Displays live **temperature and current** values.  
✅ **Buzzer Alert System:** Activates when unsafe conditions are detected.  
✅ **User-Friendly & Scalable:** Can be integrated with **power grids, industries, and renewable energy systems** for enhanced monitoring.  

## 🛠 Hardware Components  
- **Arduino (Main Controller)** – Processes sensor data and controls the system.  
- **ESP-01 ESP8266 Wi-Fi Module** – Enables IoT connectivity for remote monitoring.  
- **Current Sensor** – Measures load current and detects overcurrent conditions.  
- **Temperature Sensor** – Tracks temperature.  
- **L298N Motor Driver** – Controls the cooling fan speed dynamically.  
- **5V Relay Module** – Cuts off the load (bulb) in case of overheating or overload.  
- **LCD Display** – Shows real-time sensor readings.  
- **Buzzer** – Provides an audio warning when unsafe conditions are detected.  

## ⚙️ Working Mechanism  
1. **Data Collection:** Sensors continuously measure **temperature and current levels**.  
2. **Processing & Decision-Making:**  
   - If the **temperature crosses 70°C**, the **fan starts cooling at 50% speed**.  
   - If the **temperature exceeds 80°C**, the **fan runs at full speed**, and the **buzzer activates**.  
   - If the **current or temperature exceeds the threshold**, the **relay disconnects the load (bulb)**.  
3. **IoT-Based Monitoring:**  
   - Live data is **sent to the Blynk platform** via **ESP8266 Wi-Fi module**.  
   - Users can monitor transformer health and receive alerts on their mobile devices.  

## 💻 Technologies Used  
🟢 **Embedded Systems (Arduino, ESP8266)**  
🟢 **IoT & Cloud Connectivity (Blynk Platform)**  
🟢 **Sensor Integration (Current, Temperature)**  
🟢 **Actuator Control (Motor Driver, Relay, Buzzer)**  

## 🔮 Future Enhancements    
- **Mobile App Dashboard** for advanced analytics and historical data tracking.  
- **Multi-Transformer Support** for monitoring multiple transformers in a power grid.   

## 📜 How to Set Up  
1. **Install Required Libraries in Arduino IDE:**  
   ```cpp
   #include <Wire.h>
   #include <LiquidCrystal_I2C.h>
   #include <BlynkSimpleShieldEsp8266.h>
   ```
2. **Connect Hardware Components as per the Circuit Diagram.**  
3. **Upload the Code to Arduino.**  
4. **Set Up Blynk IoT Platform & Configure WiFi.**  
5. **Monitor Real-Time Data via Blynk Dashboard.**  

## 📌 Conclusion  
This **IoT-based Transformer Health Monitoring System** is a **cost-effective, scalable, and smart solution** for preventing transformer failures and ensuring uninterrupted power supply!   
