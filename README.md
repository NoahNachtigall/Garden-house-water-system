# 🌱 Garden House Water System

Automatisches Bewässerungssystem für ein Gartenhaus basierend auf **Arduino**.
Das System steuert eine Wasserpumpe und kann später mit Sensoren oder Zeitsteuerung erweitert werden.

---

## 📦 Features

* 💧 Steuerung einer Wasserpumpe
* ⚡ Betrieb mit Arduino
* 🔧 Einfach erweiterbar (Sensoren, WLAN, etc.)
* 🌱 Ideal für kleine Garten-Bewässerungssysteme

---

## 🛠 Hardware

Folgende Komponenten werden verwendet:

* Arduino (z. B. Arduino Uno / Nano)
* Wasserpumpe
* Relaismodul
* Netzteil
* Schläuche

Optional:

* Bodenfeuchtigkeitssensor
* Wasserstandsensor
* WLAN Modul (ESP8266 / ESP32)

---

## ⚙️ Installation

1. Repository klonen

```
git clone https://github.com/NoahNachtigall/Garden-house-water-system.git
```

2. Projekt in der Arduino IDE öffnen

3. Code auf den Arduino hochladen

---

## 📂 Projektstruktur

```
Garden-house-water-system
│
├── src
│   └── main.ino
│
├── docs
│   └── wiring-diagram.png
│
└── README.md
```

---

## 🔌 Verkabelung

| Komponente | Arduino Pin |
| ---------- | ----------- |
| Relais     | D7          |
| Sensor     | A0          |

*(Kann je nach Setup variieren)*

---

## 🚀 Geplante Features

* App Steuerung
* automatische Bewässerung
* Wetterdaten Integration
* Wasserstandüberwachung

---

## 📜 Lizenz

MIT License

---

## 👨‍💻 Autor

Noah Nachtigall
