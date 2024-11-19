#include <sil/sil.hpp>
#include "random.hpp"

//Exercice "Ne gardez que le vert"
void green_only(sil::Image& image){
    for (int x{0}; x < image.width(); x++)
{
    for (int y{0}; y < image.height(); y++)
    {
        image.pixel(x, y).r = 0;
        image.pixel(x, y).b = 0;
    }
}
}

// Échanger les canaux
void channels_swap(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x,y).r, image.pixel(x,y).b);
        }
    }
}

// Noir & Blanc
void black_white(sil::Image &image){

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        { 
            glm::vec3 &pixel = image.pixel(x, y);
            float gray = pixel.r * 0.21 + pixel.g *0.72 + pixel.b * 0.07;
            pixel.r = gray;
            pixel.g = gray;
            pixel.b = gray;
  
        }
    }
}

// Négatif
void negatif(sil::Image &image){
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        { 
            glm::vec3 &pixel = image.pixel(x, y);
            pixel.r = 1.0f - pixel.r;
            pixel.g = 1.0f - pixel.g;
            pixel.b = 1.0f - pixel.b;
  
        }
    }
}

// Dégradé
void gradiant(sil::Image &image){
    ;
    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            image.pixel(x, y) = glm::vec3{static_cast<float>(x) / static_cast<float>(image.width() - 1)};
        }
    }
}

// Miroir
void mirror(sil::Image&image){
    for (int x{0}; x < image.width()/2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        { 
         std::swap(image.pixel(x, y), image.pixel(image.width() - (x + 1), y));
        }
    } 
}

// Image bruitée
void noise(sil::Image&image){
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if(true_with_probability(0.3f)){
                image.pixel(x, y).r = random_float(0, 1);
                image.pixel(x, y).g = random_float(0, 1);
                image.pixel(x, y).b = random_float(0, 1);

            }
        }
    } 
}

// Rotation de 90°
void rotating(sil::Image&image){
    int new_width = image.height();
    int new_height = image.width();

    sil::Image new_image{new_width, new_height};
    for (int y{0}; y < new_image.height(); y++)
    {
        for (int x{0}; x < new_image.width(); x++)
        {
           new_image.pixel(x, y) =image.pixel (image.width() - 1 - y, x);
        }
    } 
    image = new_image;
}

// RGB split
void rgb_split(sil::Image&image){

}

//
int main()
{
    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        green_only(image); // Utilise la fonction pour modifier l'image
        image.save("output/green_only.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        channels_swap(image); // Utilise la fonction pour modifier l'image
        image.save("output/channels_swap.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        black_white(image); // Utilise la fonction pour modifier l'image
        image.save("output/black_white.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        negatif(image); // Utilise la fonction pour modifier l'image
        image.save("output/negatif.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{300, 200}; // Lis l'image
        gradiant(image); // Utilise la fonction pour modifier l'image
        image.save("output/gradiant.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        mirror(image); // Utilise la fonction pour modifier l'image
        image.save("output/mirror.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        noise(image); // Utilise la fonction pour modifier l'image
        image.save("output/noise.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/logo.png"};
        rotating(image); 
        image.save("output/rotating.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/logo.png"};
        rgb_split(image); 
        image.save("output/pouet.png"); // Sauvegarde l'image
    }
    // bhjgj
}