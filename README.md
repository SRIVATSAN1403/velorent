# VeloRent v2.0 — Enterprise Vehicle Rental Management System (2026 Edition)

An enterprise-grade hybrid project featuring a **C++ Core Engine** (OOP, real-time alerts, telematics, and billing) paired with an ultra-modern **Light Theme Web Portal**.

---

## 🌟 Key 2026 Innovation Features

1. **Automated Administrator Notifications (Real-Time)**:
   - When any trip is completed (`returnVehicle()`), an instant alert is dispatched to the Admin Notification Feed and logged to `admin_notifications.log`.
   - Includes vehicle ID, customer name, contact, odometer delta, remaining fuel/battery, and revenue collected.

2. **Customer Digital Invoicing & SMS Dispatch**:
   - Automated digital tax receipt generated (`Invoice_INV-2026-XXXX.txt`) with itemized pricing, VIP tier discount, late surcharge, GST (18%), and loyalty points awarded.
   - Simulation of instant SMS delivery directly to the customer's phone.

3. **2026 Smart IoT Fleet Telematics & Carbon Offset**:
   - Geofence verification upon return inside designated VeloRent hubs.
   - Battery Health Score (State of Health %) and degradation prediction for Electric Vehicles.
   - Dynamic Eco-Score & Carbon Offset Tracker (calculates exact kg of CO₂ emissions prevented vs combustion engines).
   - AI-assisted Visual Damage and Bodywork scanner (confidence rating 0-100%).

4. **Multi-Tier Customer VIP Loyalty System**:
   - Pre-configured member profiles:
     - **Srivatsan L** (`8667572257`) — Gold Tier (10% VIP Discount, 850 pts)
     - **Prasanna A** (`9696332457`) — Silver Tier (5% VIP Discount, 320 pts)
     - **Bharat J** (`9454621587`) — Platinum Tier (15% VIP Discount, 1450 pts)
   - 10 VIP reward points earned for every ₹100 spent.

5. **Redesigned Light Theme Web Portal**:
   - Crisp white / slate-50 palette (`#f8fafc`), dark high-contrast typography, refined indigo & cyan accents, subtle glassmorphic navbar, and diffuse elevation shadows.
   - Top navbar includes a live **🔔 Notification Hub** drawer tracking Admin check-ins and Customer invoices.

---

## 🚀 How to Run the C++ Project

### Option A: Using the Compiled Binary (One Click)
- Double-click **`run_cpp.bat`** or run:
  ```cmd
  VeloRent.exe
  ```

### Option B: Using Dev-C++ IDE
1. Open **Dev-C++**.
2. Go to **File -> Open Project or File** and select **`VeloRent.dev`** (or open **`main.cpp`**).
3. Press **F11** (Compile & Run) or click the **Execute -> Compile & Run** menu.

### Option C: Recompiling from Command Line
```cmd
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -std=c++11 -O2 main.cpp -o VeloRent.exe
```

---

## 🌐 How to Run the Web UI Locally (Light Theme)

1. The local web server is configured for **Port 5500**.
2. Click or open this URL in your web browser:
   👉 **http://localhost:5500/index.html**
3. To start or restart the web server at any time:
   - Double-click **`run_website.bat`**.

---

## ☁️ How to Deploy on Render (Step-by-Step)

### Step 1: Push your code to GitHub
If you haven't created a GitHub repository yet:
1. Go to [https://github.com/new](https://github.com/new)
2. Repository Name: `velorent` (Public or Private)
3. Click **Create repository** (do NOT initialize with README).
4. Run these commands in PowerShell in this folder:
   ```cmd
   git remote add origin https://github.com/SRIVATSAN1403/velorent.git
   git push -u origin main
   ```

### Step 2: Deploy to Render (Free & Instant)

#### Method A: Static Site (Recommended — 100% Free & Never Sleeps)
1. Go to [https://dashboard.render.com/](https://dashboard.render.com/) and sign in with GitHub.
2. Click the **"New +"** button at the top right and select **"Static Site"**.
3. Select your `velorent` repository.
4. Set the following settings:
   - **Name:** `velorent` (your URL will be `https://velorent.onrender.com`)
   - **Branch:** `main`
   - **Build Command:** *(leave empty)*
   - **Publish Directory:** `website`
5. Click **"Create Static Site"**.
6. Within ~30 seconds, your site is live globally with SSL!

#### Method B: Web Service (Python)
If you want to run via Python:
1. Click **"New +"** -> **"Web Service"**.
2. Connect your `velorent` repository.
3. Settings:
   - **Name:** `velorent`
   - **Runtime:** `Python 3`
   - **Build Command:** *(leave empty)*
   - **Start Command:** `python server.py`
   - **Plan:** Free
4. Click **"Create Web Service"**.

#### Method C: 1-Click Blueprint
Since this repo includes [`render.yaml`](file:///c:/Users/sriva/OneDrive/Documents/Desktop/c++/render.yaml):
1. In Render Dashboard, click **"New +"** -> **"Blueprint"**.
2. Connect your repository.
3. Render will automatically read `render.yaml` and configure both services for you!

---

## 📁 Project Directory Structure
```
c:\Users\sriva\OneDrive\Documents\Desktop\c++\
├── main.cpp                              # Core C++ 2026 System Source Code
├── VeloRent.exe                          # Pre-compiled high-performance binary
├── VeloRent.dev                          # Dev-C++ project file
├── run_cpp.bat                           # 1-Click launcher for C++ Console Application
├── run_website.bat                       # 1-Click launcher for Web UI + Browser
├── admin_notifications.log               # Persistent log of all admin alerts
├── Invoice_INV-2026-XXXX.txt             # Generated customer digital invoices
├── VeloRent_Project_Presentation.pptx    # Complete 10-slide PowerPoint presentation
└── website/                              # Light Theme Web Dashboard
    ├── index.html                        # Main Dashboard
    ├── catalog.html                      # Fleet Inventory & Search
    ├── return.html                       # Vehicle Return & Inspection
    ├── customer.html                     # Customer Hub & Digital Invoices
    ├── admin.html                        # Admin Console & Analytics
    ├── compare.html                      # Multi-Vehicle Comparison
    ├── calculator.html                   # Budget Estimator
    ├── calendar.html                     # Availability Matrix
    ├── agreement.html                    # Legal Rental Agreement
    ├── server.py                         # Local Python HTTP server (Port 5500)
    ├── css/
    │   ├── style.css                     # Modern Light Theme Design System
    │   └── components.css                # Light Theme Component Library
    └── js/
        ├── notifications.js              # 2026 Real-Time Notification & Billing Hub
        ├── ui.js                         # UI helpers, toast & notification drawer
        ├── return.js                     # Return processing & receipt generator
        ├── customer.js                   # Customer dashboard & invoice viewer
        └── data.js                       # Seed fleet & customer database
```
