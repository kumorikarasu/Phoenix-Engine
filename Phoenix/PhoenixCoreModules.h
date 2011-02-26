namespace PhoenixCore{

  class PhEntity;
  class PhPoint;

  class PhVisual
  {
    int Render(PhEntity* e); 
  };

  class PhSceneNode
  {
    PhPoint* GetPosition();
  };
}