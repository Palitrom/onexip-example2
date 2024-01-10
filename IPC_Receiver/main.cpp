// receiver.cpp
// ./receiver --hexOutput --measurementCount 10
// ./receiver --help

#include <QCoreApplication>
#include <QSharedMemory>
#include <QBuffer>
#include <QDataStream>
#include <QElapsedTimer>
#include <QDebug>

/**
 * @brief Gibt eine Hilfeanzeige für das Image-Receiver-Programm aus.
 *
 * Diese Funktion gibt eine Übersicht über die verschiedenen Optionen und deren Verwendung des Image-Receiver-Programms aus.
 * Sie ist dazu gedacht, dem Benutzer Informationen über die möglichen Befehlszeilenparameter bereitzustellen.
 */
void displayHelp() {
    qDebug() << "Usage:";
    qDebug() << "  ./image_receiver                             - Führt das Empfängerprogramm ohne spezielle Optionen aus.";
    qDebug() << "  ./image_receiver  --hexOutput                - Gibt empfangene Bilddaten im hexadezimalen Format aus.";
    qDebug() << "  ./image_receiver  --measurementCount <count> - Legt die Anzahl der Messungen für den Datentransfer fest.";
    qDebug() << "  ./image_receiver  --help                     - Zeigt diese Hilfe an und beendet das Programm.";
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
 * @brief Hauptfunktion des Image-Receiver-Programms.
 *
 * Diese Funktion überprüft die Befehlszeilenargumente, setzt die entsprechenden Optionen und führt dann den Image-Receiver aus.
 *
 * @param argc Die Anzahl der Befehlszeilenargumente.
 * @param argv Ein Array der Befehlszeilenargumente.
 * @return Der Exit-Code des Programms.
 */
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Prüfe, ob der Schalter für die hexadezimale Ausgabe vorhanden ist
    bool outputHex = false;
    for (int i = 0; i < argc; ++i) {
        if (QString(argv[i]) == "--hexOutput") {
            outputHex = true;
            break;
        }
    }

    // Prüfe, ob ein Parameter für die Anzahl der Messungen vorhanden ist
    int measurementCount = 1;  // Standardmäßig einmal messen
    for (int i = 0; i < argc - 1; ++i) {
        if (QString(argv[i]) == "--measurementCount") {
            measurementCount = QString(argv[i + 1]).toInt();
            break;
        }
    }

    // Prüfe, ob der Parameter --help übergeben wurde
    // Check whether the --help parameter was passed
    if (argc > 1 && QString(argv[1]) == "--help") {
       displayHelp();
       return 0;  // Beende das Programm nach dem Anzeigen der Hilfe
                  // After viewing help, exit the program
    }

    // IPC: Verwende QSharedMemory
    QSharedMemory sharedMemory;
    sharedMemory.setKey("MySharedMemoryKey");

    if (!sharedMemory.attach()) {
        qDebug() << "Shared memory attachment failed.";
        return -1;
    }

    // Warte darauf, dass der Sender die Daten kopiert
    sharedMemory.lock();
    sharedMemory.unlock();

    // Messe die Zeit für den Datentransfer
    QElapsedTimer transferTimer;
    transferTimer.start();

    // Empfange Bilddaten aus dem gemeinsamen Speicher
    QByteArray imageData(static_cast<const char*>(sharedMemory.constData()), sharedMemory.size());

    qint64 transferTime = transferTimer.elapsed();
    double transferFPS = (transferTime > 0) ? 1000.0 / transferTime : 0;  // Verhindere Division durch Null

    qDebug() << "Image data received. Transfer FPS:" << transferFPS;

    if (outputHex) {
       QString name = "Received Pixel";
       printPixel(imageData, name);
    }

    // Messe die Zeit für die Bildverarbeitung
    QElapsedTimer processingTimer;
    qint64 totalElapsed = 0;

    for (int i = 0; i < measurementCount; ++i) {
        processingTimer.start();

        // Verarbeite Bilddaten hier...
        // Füge hier deine Bilddatenverarbeitungslogik ein.

        qint64 elapsed = processingTimer.elapsed();
        totalElapsed += elapsed;

        qDebug() << "Image data received and processed. Elapsed time:" << elapsed << "ms";
    }

    double avgFPS = (totalElapsed > 0) ? (measurementCount * 1000.0) / totalElapsed : 0;  // Durchschnittliche FPS
    qDebug() << "Average FPS:" << avgFPS;

    // Detach und lösche den gemeinsamen Speicher
    sharedMemory.detach();

    qDebug() << "The program has terminated successfully.";
    qDebug() << "Note: You can exit the program anytime by pressing 'Ctrl+C'.";

    return a.exec();
}
