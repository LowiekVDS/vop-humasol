#include "Layers/Layer.h"
#include "Layers/LayerStack.h"
#include "Layers/PhysicalLayer.h"
#include "Layers/TransportLayer.h"
#include "Layers/EncryptionLayer.h"
#include "Layers/ApplicationLayer.h"
#include "Encryption/EncryptionType.h"

LayerStack networkStack;

ApplicationLayer applicationLayer;
void setup()
{

  // Setup NetworkStack
  networkStack.addLayer(new PhysicalLayer(433E6));
  networkStack.addLayer(new TransportLayer());
  networkStack.addLayer(new EncryptionLayer(ENC_AES));
  networkStack.addLayer(&applicationLayer);
}

void loop()
{
}