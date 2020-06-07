#include "model.h"
#include "view.h"

int main()
{
    Model model;
    model.enemies_.clear();
    View view(model);

    view.run();
}