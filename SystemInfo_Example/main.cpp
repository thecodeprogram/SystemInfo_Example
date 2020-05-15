/*
This File Created
By: Burak Hamdi TUFAN
On: https://thecodeprogram.com/
At: 16.05.2020
*/

#include <QCoreApplication>

//To use std class
#include <iostream>
using namespace std;

#include <QSysInfo>
#include <QStorageInfo>
#include <QNetworkInterface>
#include <QSettings>
#include <QProcess>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    system("title SystemInfo_Example - Thecodeprogram");
    cout << "QT C++ System Info" << endl;

    cout << "QSysInfo Class" << endl;
    cout << "CPU Architecture : " << QSysInfo::currentCpuArchitecture().toLocal8Bit().constData() << endl;
    cout << "Product Type : " << QSysInfo::prettyProductName().toLocal8Bit().constData() << endl;
    cout << "Kernel Type : " << QSysInfo::kernelType().toLocal8Bit().constData() << endl;
    cout << "Kernel Version : " << QSysInfo::kernelVersion().toLocal8Bit().constData() << endl;
    cout << "Machine ID : " << QSysInfo::machineHostName().toLocal8Bit().constData() << endl;
    cout << "-----------------------------------------------------------------" << endl;

    cout << "QStorageInfo Class" << endl;

    cout << "Mounted Volumes" << endl;
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {
        if (storage.isValid() && storage.isReady()) {
            if (!storage.isReadOnly()) {
                cout << "Name:" << storage.name().toLocal8Bit().constData() << " ";
                cout << "Root:" << storage.rootPath().toLocal8Bit().constData() << " ";
                cout << "FileSys:" << storage.fileSystemType().constData() << " ";
                cout << "Disk Spaces:";
                cout << storage.bytesAvailable()/1000000000 << "GB";
                cout << "/";
                cout << storage.bytesTotal()/1000000000 << "GB";
                cout << endl;
            }
        }
    }

    cout << "-----------------------------------------------------------------" << endl;
    cout << "QNetworkInterface Class" << endl;
    cout << "Connected Network Informations" << endl;

    foreach(QNetworkInterface networkInterface, QNetworkInterface::allInterfaces())
    {
        if (networkInterface.flags().testFlag(QNetworkInterface::IsUp) && !networkInterface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            foreach (QNetworkAddressEntry entry, networkInterface.addressEntries())
            {
                if ( entry.ip().toString().contains(".")){
                    cout << "Interface:"<< networkInterface.name().toLocal8Bit().constData() << " ";
                    cout << "IP:"<< entry.ip().toString().toLocal8Bit().constData() << " ";
                    cout << "MAC:"  << networkInterface.hardwareAddress().toLocal8Bit().constData() << endl;
                }
            }
        }
    }

    cout << "-----------------------------------------------------------------" << endl;
    cout << "QSettings Class" << endl;
    cout << "System BIOS informations. ONLY FOR WINDOWS." << endl;

    QSettings settings("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\BIOS", QSettings::NativeFormat);
    cout << "Base Manufacturer : " << settings.value("BaseBoardManufacturer", "0").toString().toLocal8Bit().constData() << endl;
    cout << "Base Product : " << settings.value("BaseBoardProduct", "0").toString().toLocal8Bit().constData() << endl;
    cout << "BIOS Vendor : " << settings.value("BIOSVendor", "0").toString().toLocal8Bit().constData() << endl;
    cout << "BIOS Release Date : " << settings.value("BIOSReleaseDate", "0").toString().toLocal8Bit().constData() << endl;
    cout << "System Manufacturer : " << settings.value("SystemManufacturer", "0").toString().toLocal8Bit().constData() << endl;
    cout << "Product Name : " << settings.value("SystemProductName", "0").toString().toLocal8Bit().constData() << endl;
    cout << "System SKU : " <<settings.value("SystemSKU", "0").toString().toLocal8Bit().constData() << endl;

    cout << "-----------------------------------------------------------------" << endl;

    QProcess process_system;
    QString system_output;

    if(QSysInfo::kernelType() == "winnt")
    {
        QString cpuname = "wmic cpu get name";
        process_system.start(cpuname);
        process_system.waitForFinished();
        system_output = process_system.readAllStandardOutput().toUpper();
        cout << "CPU : "  << system_output.toLocal8Bit().constData() << endl;


        QString gpuname = "wmic PATH Win32_videocontroller get VideoProcessor ";
        process_system.start(gpuname);
        process_system.waitForFinished();
        system_output = process_system.readAllStandardOutput();
        cout << "GPU : "  << system_output.toLocal8Bit().constData() << endl;


        QString gpuRam = "wmic PATH Win32_VideoController get AdapterRAM";
        process_system.start(gpuRam);
        process_system.waitForFinished();
        system_output = process_system.readAllStandardOutput();
        cout << "GPU RAM(Bytes) : "  << system_output.toLocal8Bit().constData() << endl;
    }

    if(QSysInfo::kernelType() == "linux")
    {
        QString linuxcpuname = "cat /proc/cpuinfo | grep 'model name' | uniq";
        process_system.start(linuxcpuname);
        process_system.waitForFinished();
        QString linuxOutput = process_system.readAllStandardOutput();
        cout << "Linux CPU Info : "  << linuxOutput.toLocal8Bit().constData() << endl;
    }


    return a.exec();
}
