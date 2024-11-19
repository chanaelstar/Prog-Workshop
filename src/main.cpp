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

    sil::Image image_split{image};

      for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {

            if(x < 30) {
                image_split.pixel(x, y).b = image.pixel(x + 30, y).b;
            } else if (x > image.width() - 31) {
                image_split.pixel(x, y).r = image.pixel(x - 30, y).r;
            } else {
                image_split.pixel(x, y).r = image.pixel(x - 30, y).r;
                image_split.pixel(x, y).b = image.pixel(x + 30, y).b;
            }
        }
    }
    image = image_split;
}

// Luminosité (éclaircissement & assombrissement)
void light_luminosity(sil::Image&image){

    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            image.pixel(x, y).r = std::sqrt(image.pixel(x, y).r);
            image.pixel(x, y).g = std::sqrt(image.pixel(x, y).g);
            image.pixel(x, y).b = std::sqrt(image.pixel(x, y).b);
        }
    }
}

void dark_Luminosity(sil::Image &image) {
    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            image.pixel(x, y).r = std::pow(image.pixel(x, y).r, 2);
            image.pixel(x, y).g = std::pow(image.pixel(x, y).g, 2);
            image.pixel(x, y).b = std::pow(image.pixel(x, y).b, 2);
        }
    }
}

// Disque 
void disk(sil::Image&image){

    int a{image.width()/2};
    int b{image.height()/2};
    int r{100};

    for (int x{0}; x < 500; ++x)
    {
        for (int y{0}; y < 500; ++y)
        {
            if((pow(x-a, 2) + pow(y-b, 2)) < pow(r, 2)) {
                image.pixel(x, y).r = 1;
                image.pixel(x, y).g = 0;
                image.pixel(x, y).b = 0;
            }
            else{
                image.pixel(x, y).r = 1;
                image.pixel(x, y).g = 1;
                image.pixel(x, y).b = 1;
                // drapeau japon 
            }
            
        }
    }
}

// Cercle 
void circle(sil::Image&image){

    int a{image.width()/2};
    int b{image.height()/2};
    int r{100};
    int thickness{10};

    for (int x{0}; x < image.width(); x++)

    {
        for (int y{0}; y < image.height(); y++)

        {
            if(pow(x-a, 2) + pow(y-b, 2) < pow(r - thickness, 2)) {
                image.pixel(x, y).r = 0;
                image.pixel(x, y).g = 0;
                image.pixel(x, y).b = 0;
            }
            else if (pow(x-a, 2) + pow(y-b, 2) < pow(r, 2)){
                image.pixel(x, y).r = 1;
                image.pixel(x, y).g = 1;
                image.pixel(x, y).b = 1;
            }

            else{
                image.pixel(x, y).r = 0;
                image.pixel(x, y).g = 0;
                image.pixel(x, y).b = 0;

            }

        }
    }
}

// Animation 
void animation(sil::Image&image){

    int a{0};
    int b{image.height()/2};
    int r{100};

    while (a < 500)
    {
        a++;
        for (int x{0}; x < 500; ++x)
        {
            for (int y{0}; y < 500; ++y)
            {
                if((pow(x-a, 2) + pow(y-b, 2)) < pow(r, 2)) {
                    image.pixel(x, y).r = 1;
                    image.pixel(x, y).g = 0;
                    image.pixel(x, y).b = 0;
                }
                else{
                    image.pixel(x, y).r = 1;
                    image.pixel(x, y).g = 1;
                    image.pixel(x, y).b = 1; 
                }
                
            }
        }
        image.save("output/anim/animation"+std::to_string(a)+".png");
    }
    
   
        
    }
    
    


// Rosace
void rosace(sil::Image &image)
{

    int r{100};
    int thickness{5};

    for (int x{0}; x < image.width(); x++)

    {
        for (int y{0}; y < image.height(); y++)

        {

            int dx = x - image.width() / 2;
            int dy = y - image.height() / 2;
            if ((dx * dx + dy * dy <= r * r) && (dx * dx + dy * dy > (r - thickness) * (r - thickness)))
            {
                image.pixel(x, y).r = 1.0f;
                image.pixel(x, y).g = 1.0f;
                image.pixel(x, y).b = 1.0f;
            }
        }
    }
    int centreX = image.width() / 2;
    int centreY = image.height() / 2;
    float angleStep = 2 * 3.14 / 6;
    for (int i = 0; i < 6; i++)
    {
        float angle = i * angleStep;
        int offsetX = static_cast<int>(r * cos(angle));
        int offsetY = static_cast<int>(r * sin(angle));

        for (int x = 0; x < image.width(); x++)
        {
            for (int y = 0; y < image.height(); y++)
            {
                int dx = x - centreX - offsetX;
                int dy = y - centreY - offsetY;

                if ((dx * dx + dy * dy <= r * r) && (dx * dx + dy * dy > (r - thickness) * (r - thickness)))
                {
                    image.pixel(x, y).r = 1.0f;
                    image.pixel(x, y).g = 1.0f;
                    image.pixel(x, y).b = 1.0f;
                }
            }
        }
    }
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
        image.save("output/rgb_split.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/photo.jpg"};
        light_luminosity(image); 
        image.save("output/light_luminosity.jpg"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/photo.jpg"};
        dark_Luminosity(image); 
        image.save("output/dark_luminosity.jpg"); // Sauvegarde l'image
    }
    {
        sil::Image image{500, 500}; // Lis l'image
        disk(image); // Utilise la fonction pour modifier l'image
        image.save("output/disk.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{500, 500}; // Lis l'image
        circle(image); // Utilise la fonction pour modifier l'image
        image.save("output/circle.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{500, 500}; // Lis l'image
        animation(image); // Utilise la fonction pour modifier l'image
    }
    {
        sil::Image image{500, 500}; // Lis l'image
        rosace(image); // Utilise la fonction pour modifier l'image
        image.save("output/rosace.png"); // Sauvegarde l'image
    }
}