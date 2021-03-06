#pragma once 

#include "synchronizer/Synchronizer.hpp"
#include "AddressBuilder.hpp"

namespace Xeth{


template<class Store, class KeyGenerator, class CipherFactory>
class GenericGenerateKeyCommand
{
    public:
        GenericGenerateKeyCommand(Store &store, Synchronizer &synchronizer);

        QVariant operator()(const QVariantMap &);

    private:
        bool generate(const QVariantMap &, std::string &address);

    private:
        Store &_store;
        Synchronizer &_synchronizer;
        KeyGenerator _keyGenerator;
        CipherFactory _cipherFactory;
};


}

#include "GenericGenerateKeyCommand.ipp"
