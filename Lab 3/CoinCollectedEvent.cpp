#include "CoinCollectedEvent.h"

CoinCollectedEvent::CoinCollectedEvent(RakNet::NetworkID _coinID, RakNet::NetworkID _collectorID) : Event(COIN_COLLECTED), coinID(_coinID), collectorID(_collectorID)
{}

CoinCollectedEvent::~CoinCollectedEvent()
{}
