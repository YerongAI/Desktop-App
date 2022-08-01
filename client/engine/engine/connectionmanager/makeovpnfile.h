#ifndef MAKEOVPNFILE_H
#define MAKEOVPNFILE_H
#include <QTemporaryFile>
#include "types/protocoltype.h"

class MakeOVPNFile
{
public:
    MakeOVPNFile();
    virtual ~MakeOVPNFile();

    bool generate(const QString &ovpnData, const QString &ip, const types::ProtocolType &protocol, uint port,
                  uint portForStunnelOrWStunnel, int mss, const QString &defaultGateway, const QString &openVpnX509,
                  bool blockOutsideDnsOption = true);
    QString path() { return path_; }

private:
    QString path_;
    QFile file_;
};

#endif // MAKEOVPNFILE_H
