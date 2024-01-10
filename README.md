# onexip-example2

---------------------- English ---------------------------------------

Shared memory project to simulate a transfer of large image data, with Qt6.

Set up two command line programs with C++. Find an IPC technology. Transfer large image data simulated
(approx. FullHD image 1920x1080x4 RGA change pixels (1920x1080x4)2 to a comprehensible value, for example 0xCF5A5ACF)
from one program to the second as efficiently as possible. Measure the data rate for data transfer in fps.

**IPC_Sender - image_sender is a Qt 6 application**
### Short description:

The program is an image transmitter program that creates a simulated FullHD image, modifies it and then sends the image data to a receiver program via shared memory.
It supports command line parameters for configuration and help.

1. **Command line parameters:**
    - `--hexOutput`: Enable hexadecimal output of the original and updated pixels.
    - `--help`: Display a help screen with the available options.

2. **Image simulation:**
    - The program simulates a FullHD image by creating a `QByteArray` (`imageData`).

3. **Hexadecimal output:**
    - When `--hexOutput` is enabled, the hexadecimal values of the original pixels before modification and the updated pixels after modification are displayed.

4. **Image modification:**
    - The second pixel of the simulated image is changed to the value `0xCF5A5ACF`.

5. **Data transfer:**
    - The program creates a QSharedMemory area to share the image data.
    - It measures the time for the data transfer process and outputs the average transfer fps.
    - The image data is copied to the shared memory.

6. **Exiting the program:**
    - The shared memory is disconnected and deleted.
    - A success message and a reminder that the program can be exited at any time by pressing 'Ctrl+C'.

### Use:

1. **Building the program:**
    - Make sure Qt 6.3.0 is installed.
    - Use CMake to configure and build the program.

2. **Run the program:**
    - Run the executable file (`image_sender`).
    - Use command line parameters as needed.

3. **Exiting the program:**
    - Quit the program by pressing 'Ctrl+C'.

The program is used to simulate, modify and then send image data via a shared memory. Depending on your needs, specific image modification or simulation logic can be implemented.

**IPC_Receiver - image_receiver is a Qt 6 application**
Here is a brief description of the program:

### Short description:

The program is an image receiver program that is used to receive and process image data from a shared memory.
It uses Qt and supports various command line parameters for configuration and help.

1. **Command line parameters:**
    - `--hexOutput`: Enable hexadecimal output of the received pixels.
    - `--measurementCount <count>`: Sets the number of measurements for image processing.
    - `--help`: Display a help screen with the available options.

2. **Shared Storage:**
    - Uses `QSharedMemory` to receive image data from a broadcast program.
    - Shared memory is identified by a predefined key (`MySharedMemoryKey`).

3. **Data transfer:**
    - After appending to shared memory, the program waits for the sender to copy the data.
    - Using `QElapsedTimer`, the time for data reception is measured and the received image data is stored in a `QByteArray`.

4. **Image processing:**
    - The times for image processing are measured using `QElapsedTimer`.
    - There is a loop for the number of measurements, and in each pass the image processing is performed (placeholder for the actual logic).

5. **Statistics and Output:**
    - The average FPS (Frames Per Second) for data reception and image processing are calculated and output.
    - Optional hexadecimal output of the received pixels if the corresponding parameter is activated.

6. **Program end:**
    - The shared memory is disconnected and deleted.
    - A success message and a reminder that the program can be exited at any time by pressing 'Ctrl+C'.

### Use:

1. **Building the program:**
    - Make sure Qt 6.3.0 is installed.
    - Use CMake to configure and build the program.

2. **Run the program:**
    - Run the executable (`image_receiver`).
    - Use command line parameters as needed.

3. **Exiting the program:**
    - Quit the program by pressing 'Ctrl+C'.

This description is intended to provide an overview of the basic functionality of the image receiver program. Depending on your needs, specific image processing algorithms can be inserted into the loop.

**Here are the basic steps to build and use the program:**

### Steps to Build:

1. **Install Qt:**
    - Make sure Qt 6.3.0 is installed on your system. You can download and install it from the official [Qt website](https://www.qt.io/download).

2. **CMake configuration:**
    - Open a terminal and navigate to the directory containing the CMake file (`CMakeLists.txt`).

3. **Execute CMake command:**
    - Run the following command to generate the CMake configuration and initialize the build system:
      on the console:
      cmake -S . -B build


4. **Perform Build:**
    - Run the build with the generated build system (e.g., Make):
      on the console:
      cmake --build build
     
    This creates the executable (image_sender) in the build directory.

### Steps to use:

1. **Run the program:**
    - Navigate to the directory where the executable was created:
      on the console:
      cd build

    - Run the program:
      on the console:
      ./image_sender
    Note that this is done in a console window, and you can exit it with `Ctrl+C`.

2. **Use command line parameters:**
    - You can add command line parameters to enable specific features, e.g.,

      on the console:
      ./image_sender --hexOutput
      for hexadecimal output.

      on the console:
      ./image_sender --help
      for displaying help.

These are the basic steps to build and use the Qt program with CMake. If you use an integrated development environment (IDE) such as Qt Creator, you may be able to do CMake configuration directly in the IDE and start the build process from there.

---------------------- Deutsch ---------------------------------------

Shared Memory Projekt zur Simulation eines Transfers großer Bilddaten, mit Qt6.

Setze zwei Kommandozeilenprogramme mit C++ auf. Finde eine IPC-Technologie. Transferiere große Bilddaten simuliert 
(ca. FullHD image 1920x1080x4 RGA ändere Pixel (1920x1080x4)2 auf einen nachvollziehbaren Wert zum Beispiel 0xCF5A5ACF) 
von einem Programm in das zweite möglichst performant. Messe die Datenrate für den Datentransfer in fps.

**IPC_Sender - image_sender ist eine Qt 6 Anwendung**
### Kurze Beschreibung:

Das Programm ist ein Bildsenderprogramm, das ein simuliertes FullHD-Bild erstellt, modifiziert und dann die Bilddaten über einen gemeinsamen Speicher an ein Empfängerprogramm sendet. 
Es unterstützt Befehlszeilenparameter für Konfiguration und Hilfe.

1. **Befehlszeilenparameter:**
   - `--hexOutput`: Aktiviert die hexadezimale Ausgabe der Original- und aktualisierten Pixel.
   - `--help`: Zeigt eine Hilfeanzeige mit den verfügbaren Optionen an.

2. **Bildsimulation:**
   - Das Programm simuliert ein FullHD-Bild, indem es eine `QByteArray` (`imageData`) erstellt.

3. **Hexadezimale Ausgabe:**
   - Wenn `--hexOutput` aktiviert ist, werden die hexadezimalen Werte der Originalpixel vor der Modifikation und der aktualisierten Pixel nach der Modifikation angezeigt.

4. **Bildmodifikation:**
   - Das zweite Pixel des simulierten Bildes wird auf den Wert `0xCF5A5ACF` geändert.

5. **Datenübertragung:**
   - Das Programm erstellt einen QSharedMemory-Bereich, um die Bilddaten zu teilen.
   - Es misst die Zeit für den Datenübertragungsvorgang und gibt die durchschnittlichen Übertragungsfps aus.
   - Die Bilddaten werden in den gemeinsamen Speicher kopiert.

6. **Beenden des Programms:**
   - Der gemeinsame Speicher wird abgetrennt und gelöscht.
   - Eine Erfolgsmeldung und eine Erinnerung, dass das Programm jederzeit durch Drücken von 'Ctrl+C' beendet werden kann.

### Verwendung:

1. **Bauen des Programms:**
   - Stelle sicher, dass Qt 6.3.0 installiert ist.
   - Verwende CMake, um das Programm zu konfigurieren und zu bauen.

2. **Ausführen des Programms:**
   - Führe die ausführbare Datei (`image_sender`) aus.
   - Verwende die Befehlszeilenparameter nach Bedarf.

3. **Beenden des Programms:**
   - Beende das Programm durch Drücken von 'Ctrl+C'.

Das Programm dient dazu, Bilddaten zu simulieren, zu modifizieren und dann über einen gemeinsamen Speicher zu senden. Je nach Bedarf können spezifische Bildmodifikations- oder Simulationslogiken implementiert werden.

**IPC_Receiver - image_receiver ist eine Qt 6 Anwendung**
Hier ist eine kurze Beschreibung des Programms:

### Kurze Beschreibung:

Das Programm ist ein Bildempfängerprogramm, das dazu dient, Bilddaten von einem gemeinsamen Speicher zu empfangen und zu verarbeiten. 
Es verwendet Qt und unterstützt verschiedene Befehlszeilenparameter für Konfiguration und Hilfe.

1. **Befehlszeilenparameter:**
   - `--hexOutput`: Aktiviert die hexadezimale Ausgabe der empfangenen Pixel.
   - `--measurementCount <count>`: Legt die Anzahl der Messungen für die Bildverarbeitung fest.
   - `--help`: Zeigt eine Hilfeanzeige mit den verfügbaren Optionen an.

2. **Gemeinsamer Speicher:**
   - Verwendet `QSharedMemory`, um Bilddaten von einem Senderprogramm zu empfangen.
   - Der gemeinsame Speicher wird durch einen vordefinierten Schlüssel (`MySharedMemoryKey`) identifiziert.

3. **Datenübertragung:**
   - Nach dem Anfügen an den gemeinsamen Speicher wartet das Programm darauf, dass der Sender die Daten kopiert.
   - Mithilfe von `QElapsedTimer` wird die Zeit für den Datenempfang gemessen, und die empfangenen Bilddaten werden in einer `QByteArray` gespeichert.

4. **Bildverarbeitung:**
   - Mithilfe von `QElapsedTimer` werden die Zeiten für die Bildverarbeitung gemessen.
   - Es gibt eine Schleife für die Anzahl der Messungen, und in jedem Durchlauf wird die Bildverarbeitung durchgeführt (Platzhalter für die eigentliche Logik).

5. **Statistiken und Ausgabe:**
   - Die durchschnittlichen FPS (Frames Per Second) für den Datenempfang und die Bildverarbeitung werden berechnet und ausgegeben.
   - Optionale hexadezimale Ausgabe der empfangenen Pixel, wenn der entsprechende Parameter aktiviert ist.

6. **Programmende:**
   - Der gemeinsame Speicher wird abgetrennt und gelöscht.
   - Eine Erfolgsmeldung und eine Erinnerung, dass das Programm jederzeit durch Drücken von 'Ctrl+C' beendet werden kann.

### Verwendung:

1. **Bauen des Programms:**
   - Stelle sicher, dass Qt 6.3.0 installiert ist.
   - Verwende CMake, um das Programm zu konfigurieren und zu bauen.

2. **Ausführen des Programms:**
   - Führe die ausführbare Datei (`image_receiver`) aus.
   - Verwende die Befehlszeilenparameter nach Bedarf.

3. **Beenden des Programms:**
   - Beende das Programm durch Drücken von 'Ctrl+C'.

Diese Beschreibung soll einen Überblick über die grundlegende Funktionalität des Bildempfängerprogramms geben. Je nach Bedarf können spezifische Bildverarbeitungsalgorithmen in die Schleife eingefügt werden.


**Hier sind die grundlegenden Schritte zum Bauen und Verwenden des Programms:**

### Schritte zum Bauen:

1. **Qt Installieren:**
   - Stelle sicher, dass Qt 6.3.0 auf deinem System installiert ist. Du kannst es von der offiziellen [Qt-Website](https://www.qt.io/download) herunterladen und installieren.

2. **CMake Konfiguration:**
   - Öffne ein Terminal und navigiere zum Verzeichnis, das die CMake-Datei (`CMakeLists.txt`) enthält.

3. **CMake Befehl Ausführen:**
   - Führe den folgenden Befehl aus, um die CMake-Konfiguration zu generieren und das Build-System zu initialisieren:
     auf der Konsole:
     cmake -S . -B build


4. **Build Durchführen:**
   - Führe den Build mit dem generierten Build-System (z.B., Make) aus:
     auf der Konsole:
     cmake --build build
     
   Dies erstellt die ausführbare Datei (image_sender) im Build-Verzeichnis.

### Schritte zum Verwenden:

1. **Ausführen des Programms:**
   - Navigiere zum Verzeichnis, in dem die ausführbare Datei erstellt wurde:
     auf der Konsole:
     cd build

   - Führe das Programm aus:
     auf der Konsole:
     ./image_sender
   Beachte, dass dies in einem Konsolenfenster erfolgt, und du kannst es mit `Ctrl+C` beenden.

2. **Befehlszeilenparameter verwenden:**
   - Du kannst Befehlszeilenparameter hinzufügen, um spezifische Funktionen zu aktivieren, z.B.,

     auf der Konsole:
     ./image_sender --hexOutput
     für die hexadezimale Ausgabe.

     auf der Konsole:
     ./image_sender --help 
     für die Anzeige der Hilfe.

Das sind die grundlegenden Schritte zum Bauen und Verwenden des Qt-Programms mit CMake. Wenn du eine integrierte Entwicklungsumgebung (IDE) wie Qt Creator verwendest, kannst du die CMake-Konfiguration möglicherweise direkt in der IDE durchführen und den Build-Prozess von dort aus starten.
