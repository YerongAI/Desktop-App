#ifndef LOCATIONMODELITEM_H
#define LOCATIONMODELITEM_H

#include <QVector>
#include "../types/pingtime.h"
#include "../types/locationid.h"

//todo: implicit sharing to avoid copy constructors
struct CityModelItem
{
    LocationID id;
    QString city;
    QString nick;
    QString countryCode;        // maybe remove
    PingTime pingTimeMs;
    bool bShowPremiumStarOnly;
    bool isFavorite;
    QString staticIpType;
    QString staticIp;
    bool isDisabled;

    QString makeTitle() const
    {
        if (id.getId() == LocationID::CUSTOM_OVPN_CONFIGS_LOCATION_ID)
        {
            return city;
        }
        else if (id.getId() == LocationID::STATIC_IPS_LOCATION_ID)
        {
            return city + "(" + staticIp + ")";
        }
        else
        {
            return city + " - " + nick;
        }
    }
};

struct LocationModelItem
{
    int initialInd_;        // ind of item without sorting
    LocationID id;
    QString title;
    QString countryCode;
    bool isShowP2P;
    bool isPremiumOnly;
    QVector<CityModelItem> cities;


    qint32 calcAveragePing() const
    {
        double averagePing = 0;
        int cnt = 0;
        for (const CityModelItem &cmi : cities)
        {
            if (!cmi.isDisabled)
            {
                if (cmi.pingTimeMs == PingTime::NO_PING_INFO)
                {
                    averagePing += 200;     // we assume a maximum ping time for three bars
                }
                else if (cmi.pingTimeMs == PingTime::PING_FAILED)
                {
                    averagePing += 2000;    // 2000 - max ping interval
                }
                else
                {
                    averagePing += cmi.pingTimeMs.toInt();
                }
                cnt++;
            }
        }
        if (cnt > 0)
        {
            return averagePing / (double)cnt;
        }
        else
        {
            return -1;
        }
    }

};

#endif // LOCATIONMODELITEM_H
