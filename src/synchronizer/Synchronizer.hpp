#pragma once

#include <QObject>

#include "ethrpc/Provider.hpp"
#include "ethrpc/BlockChain.hpp"

#include "ChainProgressFetcher.hpp"
#include "ChainScanner.hpp"

namespace Xeth{


class Synchronizer : public QObject
{
    Q_OBJECT
    public:
        typedef Xeth::ChainProgressFetcher SyncProgress;

    public:
        Synchronizer(Ethereum::Connector::Provider &, DataBase &);

        void synchronize(size_t scanInterval = 12000, size_t syncInterval = 12000);
        void stop();

        void watchAddress(const std::string &);
        void watchAddress(const std::string &, time_t);

        void watch(const EthereumKey &);
        void watch(const Ethereum::Address &);
        void watch(const StealthKey &);

        void watch(const EthereumKey &, time_t);
        void watch(const Ethereum::Address &, time_t);
        void watch(const StealthKey &, time_t);


        void loadAddresses();


    public slots:

        double getChainProgress() const;
        double getScanProgress() const;
        bool   isActive() const;

   signals:
        void ScanProgress(double) const;
        void ChainProgress(double) const;

    private slots:
        void emitScanProgress(double);
        void emitChainProgress(double);

    private:
        SyncProgress _syncProgress;
        ChainScanner _scanner;
};

}