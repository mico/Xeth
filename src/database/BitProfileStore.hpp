#pragma once

#include <QObject>
#include "bitprofile/Network.hpp"
#include "bitprofile/ProfileDescriptor.hpp"
#include "bitprofile/ProfileStore.hpp"


namespace Xeth{


class BitProfileStore : public QObject
{
    Q_OBJECT
    public:
        typedef BitProfile::ProfileStore::Iterator Iterator;

    public:
        BitProfileStore(BitProfile::Network);

        bool insert(const BitProfile::ProfileDescriptor &);
        bool remove(const BitProfile::Profile::URI &);
        bool remove(const QString &uri);

        Iterator begin() const;
        Iterator end() const;

    signals:
        void NewItem(const BitProfile::ProfileDescriptor &) const;
        void Removed(const QString &uri) const;


    private:
        BitProfile::ProfileStore _store;

};


}