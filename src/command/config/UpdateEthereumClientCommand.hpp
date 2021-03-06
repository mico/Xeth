#pragma once

#include <QVariant>
#include <QFileInfo>
#include <QString>
#include <QFile>
#include <QCoreApplication>

#include <boost/filesystem.hpp>


#include "conf/Settings.hpp"
#include "io/ApplicationPath.hpp"
#include "process/ProcessSupervisor.hpp"
#include "process/EthProcessFactory.hpp"
#include "synchronizer/Synchronizer.hpp"



namespace Xeth{


class UpdateEthereumClientCommand
{
    public:
        UpdateEthereumClientCommand(ProcessSupervisor &, Synchronizer &, const Settings &);
        QVariant operator()(const QString &);

    private:
        void backupIfExists(const QString &, const QString &);
        QString makeBinPath(const QString &, const QFileInfo &);
        QString getVendorsPath();
        void createIfNotExists(const QString &);

    private:
        ProcessSupervisor &_client;
        Synchronizer &_synchronizer;
        const Settings &_settings;
};


}
