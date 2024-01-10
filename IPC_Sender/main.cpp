// sender.cpp
// ./sender --hexOutput --help

#include <QBuffer>
#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>
#include <QElapsedTimer>
#include <QSharedMemory>

#include <iostream>

// Constants
const int WIDTH = 1920;
const int HEIGHT = 1080;
const int CHANNELS = 4;
const QByteArray PIXEL_VALUE = QByteArray::fromHex("CF5A5ACF");

/**
 * @brief Gibt eine Hilfeanzeige für das Image-Sender-Programm aus.
 *
 * Diese Funktion zeigt eine Übersicht über die verschiedenen Optionen und deren Verwendung für das Image-Sender-Programm an.
 * Sie ist dazu gedacht, dem Benutzer Informationen über die möglichen Befehlszeilenparameter bereitzustellen.
 */
void displayHelp() {
    qDebug() << "Usage:";
    qDebug() << "  ./image_sender              - Führt das Programm ohne spezielle Optionen aus.";
    qDebug() << "  ./image_sender --hexOutput  - Gibt Bilddaten im hexadezimalen Format aus.";
    qDebug() << "  ./image_sender --help       - Zeigt diese Hilfe an und beendet das Programm.";
}

/**
 * @brief Simuliert ein FullHD-Bild in der übergebenen ByteArray.
 *
 * Diese Funktion füllt die übergebene Bilddaten-ByteArray mit einem simulierten FullHD-Bild, um als Testdaten zu dienen.
 * Das Bild besteht aus Pixeln mit RGBA-Werten, die auf 0xCF gesetzt sind, und einem zusätzlichen 32-Bit-Wert am Ende.
 *
 * @param imageData Die ByteArray, die mit den simulierten Bilddaten gefüllt werden soll.
 */
void simulateImage(QByteArray &imageData) {
    // Fülle die ByteArray mit RGBA-Werten von 0xCF
    imageData.fill(0xCF);

    // Erstelle einen Datenstrom und setze die Position auf das Ende der Bilddaten
    QDataStream stream(&imageData, QIODevice::WriteOnly);
    stream.device()->seek((WIDTH * HEIGHT * CHANNELS) * 2);

    // Schreibe einen 32-Bit-Wert (0xCF5A5ACF) am Ende der simulierten Bilddaten
    stream << static_cast<quint32>(0xCF5A5ACF);
}

/**
 * @brief Gibt Informationen über die ersten vier Pixel in der übergebenen Bilddaten-ByteArray aus.
 *
 * Diese Funktion extrahiert die RGBA-Werte der ersten vier Pixel aus der gegebenen Bilddaten-ByteArray und gibt
 * sie sowohl in dezimaler als auch in hexadezimaler Form aus. Der Parameter `pixelName` wird verwendet, um den
 * Namen oder die Bezeichnung der Pixel in den Ausgabemeldungen anzugeben.
 *
 * @param imageData Die Bilddaten-ByteArray, aus der die Informationen extrahiert werden sollen.
 * @param pixelName Der Name oder die Bezeichnung der Pixel, der in den Ausgabemeldungen verwendet wird.
 */
void printPixel(QByteArray &imageData, QString &pixelName) {
    // Annahme: RGBA-Daten, jeweils ein Byte pro Kanal
    int bytesPerPixel = 4;

    // Extrahiere die ersten vier Pixel
    QByteArray firstFourPixels = imageData.left(bytesPerPixel * 4);

    // Gib die Dezimalwerte der RGBA-Kanäle aus
    qDebug() << "\nFirst four pixels (RGBA):";

    for (int i = 0; i < 4; ++i) {
        int startIndex = i * bytesPerPixel;
        uchar red = static_cast<uchar>(firstFourPixels[startIndex]);
        uchar green = static_cast<uchar>(firstFourPixels[startIndex + 1]);
        uchar blue = static_cast<uchar>(firstFourPixels[startIndex + 2]);
        uchar alpha = static_cast<uchar>(firstFourPixels[startIndex + 3]);

        qDebug() << pixelName << i << ": R=" << red << ", G=" << green << ", B=" << blue << ", A=" << alpha;
    }

    // Gib die hexadezimalen Werte der RGBA-Kanäle aus
    qDebug() << "First four pixels (hex):";

    for (int i = 0; i < 4; ++i) {
        int startIndex = i * bytesPerPixel;

        uchar red = static_cast<uchar>(firstFourPixels[startIndex]);
        uchar green = static_cast<uchar>(firstFourPixels[startIndex + 1]);
        uchar blue = static_cast<uchar>(firstFourPixels[startIndex + 2]);
        uchar alpha = static_cast<uchar>(firstFourPixels[startIndex + 3]);

        qDebug() << pixelName << i << ": R=" << QString("%1").arg(red, 2, 16, QChar('0')).toUpper()
                 << ", G=" << QString("%1").arg(green, 2, 16, QChar('0')).toUpper()
                 << ", B=" << QString("%1").arg(blue, 2, 16, QChar('0')).toUpper()
                 << ", A=" << QString("%1").arg(alpha, 2, 16, QChar('0')).toUpper();
    }

    qDebug() << "\n";
}

/**
 * @brief Hauptfunktion des Image-Sender-Programms.
 *
 * Diese Funktion überprüft die Befehlszeilenargumente und führt entsprechende Aktionen aus. Sie simuliert dann ein FullHD-Bild
 * und gibt optional die hexadezimalen Werte der Originalpixel aus.
 *
 * @param argc Die Anzahl der Befehlszeilenargumente.
 * @param argv Ein Array der Befehlszeilenargumente.
 * @return Der Exit-Code des Programms.
 */
int main(int argc, char *argv[]) {
   QCoreApplication a(argc, argv);

   // Prüfe, ob ein Parameter für die Anzeige von imageData.toHex() vorhanden ist
   // Check if there is a parameter for displaying imageData.toHex()
   bool outputHex = false;
   for (int i = 0; i < argc; ++i) {
      if (QString(argv[i]) == "--hexOutput") {
         outputHex = true;
         break;
      }
   }

   // Prüfe, ob der Parameter --help übergeben wurde
   // Check whether the --help parameter was passed
   if (argc > 1 && QString(argv[1]) == "--help") {
      displayHelp();
      return 0; // Beende das Programm nach dem Anzeigen der Hilfe
      // After viewing help, exit the program
   }

   // Simuliere ein FullHD-Bild
   // Simulate a FullHD image
   QByteArray imageData(WIDTH * HEIGHT * CHANNELS, 0);
   simulateImage(imageData);



   if(outputHex){
     QString name = "Orginal Pixel";
     printPixel(imageData, name);
   }


   // Beispiel: Ändere zweites Pixel (1920x1080x4)2 auf 0xCF5A5ACF
   // Example: Change pixels (1920x1080x4)2 to 0xCF5A5ACF
   *reinterpret_cast<quint32 *>(imageData.data() + CHANNELS) = 0xCF5A5ACF;

   // Schreiben Sie die aktualisierte imageData zurück in QDataStream
   QDataStream stream(&imageData, QIODevice::WriteOnly);

   // Stellen Sie sicher, dass der Schreibkopf des Datenstroms am Anfang
   // positioniert ist
   stream.device()->seek(0);

   // Schreiben Sie den gesamten aktualisierten Datenstrom zurück in imageData
   stream << imageData;

   if (outputHex) {
      QString name = "Update Pixel";
      printPixel(imageData, name);
   }

   // IPC: Verwende QSharedMemory
   // IPC: Use QSharedMemory
   QSharedMemory sharedMemory;
   sharedMemory.setKey("MySharedMemoryKey");

   // Falls der gemeinsame Speicher bereits existiert, entferne ihn
   // If shared storage already exists, remove it
   if (sharedMemory.attach()) {
      sharedMemory.detach();
   }

   if (!sharedMemory.create(imageData.size())) {
      qDebug() << "Shared memory creation failed.";
      return -1;
   }

   // Messe die Zeit für den Datentransfer
   // Measure the time for data transfer
   QElapsedTimer transferTimer;
   qint64 totalTransferTime = 0;
   transferTimer.start();

   // Kopiere Bilddaten in den gemeinsamen Speicher
   // Copy image data to shared storage
   sharedMemory.lock();
   memcpy(sharedMemory.data(), imageData.constData(), imageData.size());
   sharedMemory.unlock();

   // if (outputHex) {
   //   qDebug() << "Sent image data (hex):" << imageData.toHex();
   //  }

   qint64 transferTime = transferTimer.elapsed();
   totalTransferTime += transferTime;

   qDebug() << "Image data sent to shared memory. Transfer time:" << transferTime
            << "ms";

   double avgTransferFPS = (totalTransferTime > 0)
         ? (1 * 1000.0) / totalTransferTime
         : 0; // Durchschnittliche FPS für 1 Durchlauf
   qDebug() << "Average transfer FPS:" << avgTransferFPS;

   qDebug() << "The program has terminated successfully.";
   qDebug() << "Note: You can exit the program anytime by pressing 'Ctrl+C'.";

   return a.exec();
}
