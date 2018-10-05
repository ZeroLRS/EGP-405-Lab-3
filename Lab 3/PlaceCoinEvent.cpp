#include "PlaceCoinEvent.h"



PlaceCoinEvent::PlaceCoinEvent(Entity _coinData) : Event(PLACE_COIN), coinData(_coinData)
{
}


PlaceCoinEvent::~PlaceCoinEvent()
{
}
