#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

emp::web::Document doc{"target"};

class GradientAnimator : public emp::web::Animate {
    int number = 0;
    int num_w_boxes = 15, num_h_boxes = 10; 
    emp::web::Canvas canvas{100, 100, "canvas"};
    
    std::vector<std::vector<float>> cells;
    std::vector<std::vector<float>> nextCells;

    public: 
    GradientAnimator() {
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");
        
        cells.resize(num_w_boxes, std::vector<float>(num_h_boxes, 0));
        nextCells.resize(num_w_boxes, std::vector<float>(num_h_boxes, 0));
        // Initialize all cells with 1
        for (int i = 0; i < num_w_boxes; i++) {
            for (int j = 0; j < num_h_boxes; j++) {
                cells[i][j] = 1;
            }
        }
        cells[1][2] = 1;
        cells[2][4] = 0.8;
    }
    
    void DoFrame() override{
        canvas.Clear();
        // Calculate next state based on neighbor values
        for (int i = 0; i < num_w_boxes; i++) {
            for (int j = 0; j < num_h_boxes; j++) {
                nextCells[i][j] = cells[(i + 1) % num_w_boxes][j];
            }
        }

        cells = nextCells;

        //draw cells
        for (int i = 0; i < num_w_boxes; i++) {
            for (int j = 0; j < num_h_boxes; j++) {
                float value = nextCells[i][j];
                canvas.Rect(i * 10, j * 10, 10, 10, emp::ColorHSV(0, 0, value), "black");
            }
        }
}
};



GradientAnimator animator;

int main() {
    animator.Step();
    return 0;
    };
