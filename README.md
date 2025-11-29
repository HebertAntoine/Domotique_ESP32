# Domotique_ESP32# 🏠 ESP8266 + HomeKit – Petits modules de domotique

Ce projet a pour but de créer **des petits modules simples de domotique** basés sur un **ESP8266**, pilotables depuis l’app **Maison (HomeKit) d’Apple**.

L’idée est de faire :

- des **modules indépendants** (un capteur, un relais, etc.)
- faciles à flasher
- configurables en Wi-Fi via un **portail captif** (WiFiManager)
- visibles dans **HomeKit** comme si c’était des accessoires “officiels”.

---

## 📁 Fichiers du projet

Actuellement le projet est organisé autour de **deux types de modules** :

### 1. `sketch_dht11_homekit.ino` – Capteur Température & Humidité

Module basé sur :

- **ESP8266** (NodeMCU, Wemos D1 mini…)
- **Capteur DHT11** connecté sur `D3` (GPIO0)

Fonctions :

- Lit la **température** et l’**humidité** via le DHT11.
- Envoie régulièrement les valeurs à **HomeKit** :
  - 1 service “Température”
  - 1 service “Humidité relative”
- Utilise **WiFiManager** pour configurer le Wi-Fi via un portail captif :
  - Au premier démarrage, l’ESP crée un Wi-Fi du type `DHT11_Setup`
  - Tu t’y connectes avec ton iPhone → une page s’ouvre pour choisir le Wi-Fi de ta maison
- Utilise la librairie **HomeKit-ESP8266** pour exposer les caractéristiques à l’app Maison.

Ce que tu vois dans l’app Maison :

- Une tuile “Capteur” qui affiche la **température**
- Dans les détails du capteur, tu peux aussi consulter l’**humidité**

---

### 2. `sketch_relay_homekit.ino` – Relais / Interrupteur On/Off

Module basé sur :

- **ESP8266**
- **Relais** connecté sur une sortie (par ex. `D1` ou `D2`, selon ton câblage)

Fonctions :

- Contrôle un **relais** (interrupteur on/off) pour alimenter :
  - une lampe,
  - un ventilateur,
  - une prise, etc. (⚠️ attention au 230V, toujours avec des modules prévus pour !)
- Exposé à **HomeKit** comme un **interrupteur** / prise :
  - tu peux l’allumer / l’éteindre depuis l’app Maison
  - tu peux l’intégrer dans des scènes / automatisations
- Utilise le même mécanisme de **portail Wi-Fi** (WiFiManager) que le capteur :
  - réseau type `Relay_Setup` au premier démarrage
- Utilise aussi **HomeKit-ESP8266** pour la partie accessoire.

Ce que tu vois dans l’app Maison :

- Une tuile “Interrupteur” ou “Prise” (nom : “Relais ESP” par exemple)
- Tu peux cliquer dessus pour ON/OFF, ou dire à Siri :
  - « Hé Siri, allume le relais »
  - « Hé Siri, éteins le relais »

---

## 🔧 Matériel requis

- 1x **ESP8266** (NodeMCU, Wemos D1 mini, etc.)
- Pour le module **Température/Humidité** :
  - 1x **DHT11**
  - Quelques fils Dupont (ou un module Grove adapté)
- Pour le module **Relais** :
  - 1x **Module relais 3,3V ou 5V** compatible logique 3,3V
- Un **câble micro-USB** (données) pour flasher l’ESP
- Un **Mac / PC** avec l’IDE Arduino installé

---

## 📚 Librairies Arduino nécessaires

À installer via le **Gestionnaire de bibliothèques** ou manuellement :

- `ESP8266WiFi` (incluse avec le core ESP8266)
- `DNSServer`
- `ESP8266WebServer`
- `WiFiManager` (pour le portail de config Wi-Fi)
- `DHT sensor library` (Adafruit)
- `Adafruit Unified Sensor`
- `HomeKit-ESP8266` (par Mixiaoxiao / arduino-homekit-esp8266)

Et via le **Gestionnaire de cartes** :

- Core **"esp8266 by ESP8266 Community"**

---

## ⚙️ Compilation & Flash

1. Ouvrir l’IDE Arduino.
2. Installer le **core ESP8266** si ce n’est pas déjà fait.
3. Dans **Outils → Type de carte**, choisir :
   - `NodeMCU 1.0 (ESP-12E Module)` (ou la carte ESP8266 que tu utilises).
4. Sélectionner le **port série** (`/dev/cu.usbserial-xxxx` sur macOS).
5. Ouvrir :
   - `sketch_dht11_homekit.ino` pour le module capteur  
   ou
   - `sketch_relay_homekit.ino` pour le relais
6. Vérifier tout en haut du fichier que les **pins** correspondent à ton câblage (D3 pour le DHT11, D1/D2 pour le relais, etc.).
7. Cliquer sur **Téléverser**.

---

## 🌐 Configuration du Wi-Fi (portail captif)

Au **premier démarrage** (ou après effacement des paramètres Wi-Fi), l’ESP :

1. Passe en mode point d’accès (AP).
2. Crée un Wi-Fi du type :
   - `DHT11_Setup` pour le capteur
   - `Relay_Setup` pour le relais (selon ce que le code définit)

### Étapes sur l’iPhone :

1. Ouvre les **réglages Wi-Fi**.
2. Connecte-toi au réseau :
   - `DHT11_Setup` ou `Relay_Setup`.
3. Une **page de configuration** doit s’ouvrir automatiquement :
   - Si ce n’est pas le cas, ouvre Safari et va sur `http://192.168.4.1`.
4. Choisis ton **SSID** (Wi-Fi de ta box).
5. Entre le **mot de passe Wi-Fi**.
6. Valide.

L’ESP8266 va alors :

- Sauvegarder ces infos dans sa mémoire.
- Rebooter et se connecter automatiquement à ce Wi-Fi à chaque démarrage.

---

## 🏡 Connexion à HomeKit (App Maison)

Une fois que :

- L’ESP8266 est **connecté à ton Wi-Fi** de maison.
- Le code HomeKit est bien flashé.

Alors tu peux l’ajouter dans **Maison**.

### Étapes :

1. Vérifie que ton iPhone est sur le **même Wi-Fi** que l’ESP8266.
2. Ouvre l’app **Maison**.
3. Appuie sur **"+"** en haut à droite → **"Ajouter un accessoire"**.
4. Choisis **"Plus d’options…"** (ou “Je n’ai pas de code ou je ne peux pas le scanner”).
5. Attends que l’accessoire apparaisse dans la liste :
   - Par exemple : `Capteur DHT11` ou `Relais ESP`.
6. Sélectionne l’accessoire.
7. Quand l’app demande le **code HomeKit** :
   - entre le **code défini dans la config HomeKit** (par exemple `111-11-111` si le code a été défini comme ça dans `config`).
8. Donne un **nom** à l’accessoire (Salon, Chambre, etc.) et attribue une **pièce**.

L’accessoire est maintenant enregistré dans HomeKit, disponible sur :

- iPhone / iPad
- Apple Watch
- HomePod / Apple TV (qui servent de concentrateur)

---

## 👀 Ce que tu verras dans l’app Maison

### Capteur Température & Humidité (`sketch_dht11_homekit.ino`)

- Une tuile avec le nom du capteur (ex. “Capteur DHT11”).
- Affichage de la **température** sur la tuile.
- En touchant la tuile, tu peux voir :
  - Température actuelle
  - Humidité relative en %

Tu peux ensuite :

- Créer des automatisations (ex. si température > X → envoyer une notif).
- Ajouter dans des scènes (ex. “Mode Reptile”, “Mode Nuit”, etc.).

### Relais / Interrupteur (`sketch_relay_homekit.ino`)

- Une tuile d’interrupteur (On/Off).
- Un simple tap → bascule le relais (ON/OFF).
- Tu peux renommer le relais (ex. “Lumière Terrarium”).
- Tu peux l’inclure dans des scènes / automatisations :
  - “Quand je rentre à la maison → allumer le relais”
  - “À 23h → éteindre le relais”

---

## 🎯 Objectif global du projet

L’objectif est de construire **une collection de petits modules ESP8266** :

- Faciles à **fabriquer** et à **flasher**
- Qui se **configurent tout seuls** côté Wi-Fi via un portail
- Qui parlent **HomeKit nativement** (via HomeKit-ESP8266)
- Pour faire évoluer petit à petit ta maison en **domotique DIY** :
  - capteurs (température, humidité, consommation, etc.)
  - actionneurs (relais, lumières, prises, ventilateurs…)

L’idée est que chaque fichier `.ino` corresponde à un **module simple**, plug-and-play :

- Tu flashes
- Tu configures le Wi-Fi
- Tu ajoutes dans l’app Maison
- Et c’est parti 🚀

---