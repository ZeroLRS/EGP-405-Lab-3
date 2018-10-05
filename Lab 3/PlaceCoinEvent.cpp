#include "PlaceCoinEvent.h"



PlaceCoinEvent::PlaceCoinEvent(Vector2 _coinPos) : Event(PLACE_COIN), coinPos(_coinPos)
{
}


PlaceCoinEvent::~PlaceCoinEvent()
{
}
