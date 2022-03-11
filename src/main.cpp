#include "Layers/Layers.h"
#include "Layers/LayerStack.h"
#include "Encryption/EncryptionType.h"

LayerStack networkStack;

ApplicationLayer applicationLayer;
void setup()
{

  // Setup NetworkStack
  networkStack.addLayer(&PhysicalLayer::GetInstance());
  networkStack.addLayer(new TransportLayer());
  networkStack.addLayer(new EncryptionLayer(ENC_AES));
  networkStack.addLayer(&applicationLayer);

}

void loop()
{
}