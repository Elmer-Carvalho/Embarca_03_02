#define INT 0.5
#define QUANT_FRAMES 11
#define LARG 5
#define ALTU 5

static const float frames[QUANT_FRAMES][LARG][ALTU] = {
    {
        {0.0, INT, INT, INT, 0.0},
        {0.0, INT, 0.0, INT, 0.0},
        {0.0, INT, 0.0, INT, 0.0}, // 0
        {0.0, INT, 0.0, INT, 0.0},
        {0.0, INT, INT, INT, 0.0}
    },
    {
        {0.0, 0.0, INT, 0.0, 0.0},
        {0.0, INT, INT, 0.0, 0.0},
        {0.0, 0.0, INT, 0.0, 0.0}, // 1
        {0.0, 0.0, INT, 0.0, 0.0},
        {0.0, INT, INT, INT, 0.0}
    },
    {
        {0.0, INT, INT, INT, 0.0},
        {0.0, 0.0, 0.0, INT, 0.0},
        {0.0, INT, INT, INT, 0.0}, // 2
        {0.0, INT, 0.0, 0.0, 0.0},
        {0.0, INT, INT, INT, 0.0}
    },
    {
        {0.0, INT, INT, INT, 0.0},
        {0.0, 0.0, 0.0, INT, 0.0},
        {0.0, 0.0, INT, INT, 0.0}, // 3
        {0.0, 0.0, 0.0, INT, 0.0},
        {0.0, INT, INT, INT, 0.0}
    },
    {
        {0.0, INT, 0.0, INT, 0.0},
        {0.0, INT, 0.0, INT, 0.0},
        {0.0, INT, INT, INT, 0.0}, // 4
        {0.0, 0.0, 0.0, INT, 0.0},
        {0.0, 0.0, 0.0, INT, 0.0}
    },
    {
        {0.0, INT, INT, INT, 0.0},
        {0.0, INT, 0.0, 0.0, 0.0},
        {0.0, INT, INT, INT, 0.0}, // 5
        {0.0, 0.0, 0.0, INT, 0.0},
        {0.0, INT, INT, INT, 0.0}
    },
    {
        {0.0, INT, INT, INT, 0.0},
        {0.0, INT, 0.0, 0.0, 0.0},
        {0.0, INT, INT, INT, 0.0}, // 6
        {0.0, INT, 0.0, INT, 0.0},
        {0.0, INT, INT, INT, 0.0}
    },
    {
        {0.0, INT, INT, INT, 0.0},
        {0.0, 0.0, 0.0, INT, 0.0},
        {0.0, 0.0, 0.0, INT, 0.0}, // 7
        {0.0, 0.0, 0.0, INT, 0.0},
        {0.0, 0.0, 0.0, INT, 0.0}
    },
    {
        {0.0, INT, INT, INT, 0.0},
        {0.0, INT, 0.0, INT, 0.0},
        {0.0, INT, INT, INT, 0.0}, // 8
        {0.0, INT, 0.0, INT, 0.0},
        {0.0, INT, INT, INT, 0.0}
    },
    {
        {0.0, INT, INT, INT, 0.0},
        {0.0, INT, 0.0, INT, 0.0},
        {0.0, INT, INT, INT, 0.0}, // 9
        {0.0, 0.0, 0.0, INT, 0.0},
        {0.0, 0.0, 0.0, INT, 0.0}
    },
    {
        {0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0}, // LIMPAR LEDS
        {0.0, 0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0}
    }
};