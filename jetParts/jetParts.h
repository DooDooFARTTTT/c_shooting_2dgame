


typedef struct {
    float peso;
    float costo;
    float resistenza;
    float turn_capability;
    float perfect_turn_speed;
} Wings;

typedef struct{
    float peso;
    float costo;
    float resistenza;
    float potenza;
} Engine;

typedef struct{
    float peso;
    float costo;
    float resistenza;
    float aereodinamicita;
    float aereofreno;
} Airframe;

typedef struct{
    float peso;
    float costo;
    float damage_per_bullet;
    float munizioni;
    float firerate;
    float ricarica_rimasta;
} Gun;