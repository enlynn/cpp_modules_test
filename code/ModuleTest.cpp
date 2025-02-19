import std;

import BasicPlane.Figures;

int main()
{
    // I am not sure how I feel about imports placing module symbols into the default
    // namespace. I could wrap exported symbols into a namespace to solve this.
    Rectangle r{ {1,8}, {11,3} };

    std::cout << "area:  " << area(r)  << std::endl;
    std::cout << "width: " << width(r) << std::endl;
}
