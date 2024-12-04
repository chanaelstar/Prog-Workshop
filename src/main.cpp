#include <sil/sil.hpp>
#include "random.hpp"
#include <algorithm>
#include "sous_fonction/sous_fonction.hpp"
#include <complex>
#include <iostream>
#include <glm/gtx/matrix_transform_2d.hpp>

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
            float gray = brightness(pixel);
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

    sil::Image image_split{image.width(), image.height()};

      for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {

            if(x >= 30) {
                image_split.pixel(x, y).r = image.pixel(x - 30, y).r;
            } 
             if (x < image.width() - 31) {
                image_split.pixel(x, y).b = image.pixel(x + 30, y).b;
            } 
                image_split.pixel(x, y).g = image.pixel(x, y).g;
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


// Animation bonus 
void animation_bonus(sil::Image&image){

    int a{0};
    while (a < 500)
    {
        a++;
    int b{300*(1-square((a-250.f)/250.f))};// b == center_y
    int r{100*(1-square((a-250.f)/250.f))};
    

    // float couleur{(glm::vec3 color)};
    // couleur de la lune 
    glm::vec3 white{1, 1, 1};
    glm::vec3 red{1,0,0};
    // couleur du ciel 
    glm::vec3 blue{0, 0, 1};
    glm::vec3 bordeaux{0.51776470588f, 0.121568275f, 0.1921568627f};


float pourcentage = (1-square((a-250.f)/250.f)); //static_cast<float>(a) / static_cast<float>(250);
// if(pourcentage > 1)
// pourcentage = 1;
    glm::vec3 color_sun{glm::mix(white, red, pourcentage)};
    glm::vec3 color_sky{glm::mix(blue, bordeaux, pourcentage)};


        for (int x{0}; x < 500; ++x)
        {
            for (int y{0}; y < 500; ++y)
            {
                float distance = sqrt((pow(x-a, 2) + pow(y-b, 2)));
                if(distance <r) {
                    image.pixel(x, y) = color_sun;
                }
                else if (distance < r + 50)
                {
                   float p2 = (distance - r) / 50;
                    image.pixel(x, y)= glm::mix(color_sun, color_sky, p2 );
                }
                
                else{
                    image.pixel(x, y)= color_sky;
                
                }  
            }
        }
        image.save("output/anim_bonus/animation"+std::to_string(a)+".png");
    }    
    }
    
// Rosace
void rosace(sil::Image &image){

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

// Mosaïque
void mosaic(sil::Image &image){
    // Dimensions de la mosaïque
    int new_width = image.width() * 5;
    int new_height = image.height() * 5;

    sil::Image new_image{new_width, new_height};

    for (int x = 0; x < new_width; ++x)
    {
        for (int y = 0; y < new_height; ++y)
        {
            int old_x = x % image.width();
            int old_y = y % image.height();

            new_image.pixel(x, y) = image.pixel(old_x, old_y);
        }
    }
    image = new_image;
}

// Mosaïque mirroir 
void mosaic_mirror(sil::Image&image){

    sil::Image mosaic{image.width() * 5, image.height() * 5};

    for(int x{0}; x < mosaic.width(); x++) 
    {
        for(int y{0}; y < mosaic.height(); y++)
        {
            int old_x {x % image.width()};
            int old_y {y % image.height()};

            bool mirrorX {(x / image.width()) % 2 == 1};
            bool mirrorY {(y / image.height()) % 2 == 1}; 

            if (mirrorX) {
                old_x = image.width() - old_x - 1;
            }
            if (mirrorY) {
                old_y = image.height() - old_y - 1;
            }

            mosaic.pixel(x, y) = image.pixel(old_x, old_y);
        }
    }
    image = mosaic;
}

// Glitch
void glitch(sil::Image &image){
    int number_glitch = 100;

    for (int i = 0; i < number_glitch; ++i)
    {
        int rectangle1_x = random_int(0, image.width() - 1);
        int rectangle1_y = random_int(0, image.height() - 1);
        int rectangle_width = random_int(image.width()/20, image.width()/8); 
        int rectangle_height = random_int(image.height()/100, image.height()/30); 

        int rectangle2_x = random_int(0, image.width() - 1);
        int rectangle2_y = random_int(0, image.height() - 1);

        rectangle_width = std::min(rectangle_width, image.width() - std::max(rectangle1_x, rectangle2_x));
        rectangle_height = std::min(rectangle_height, image.height() - std::max(rectangle1_y, rectangle2_y));

        for (int x = 0; x < rectangle_width; ++x)
        {
            for (int y = 0; y < rectangle_height; ++y)
            {
                std::swap(image.pixel(rectangle1_x + x, rectangle1_y + y), image.pixel(rectangle2_x + x, rectangle2_y + y));
            }
        }
    }
}

// Tri de pixels
void pixel_sorting(sil::Image &image){

    for (int i=0; (i + 70) < image.pixels().size(); i++)
    {
        if (random_int(0, 150) == 75){
            std::sort(image.pixels().begin() + i, image.pixels().begin() + (i + 70), [](glm::vec3 const& color1, glm::vec3 const& color2)
            {
            return brightness(color1) > brightness(color2);
            });
            i = i + 70;
        }
    }
}

// Dégradé couleur
void gradiant_color(sil::Image&image, glm::vec3 color1, glm::vec3 color2 ){
    color1 = linear_to_oklab (color1);
    color2=  linear_to_oklab (color2);
    for (int x{0}; x < image.width(); ++x)
    {
        for (int y{0}; y < image.height(); ++y)
        {
            // image.pixel(x, y) = glm::mix(color1, color2, static_cast<float>(x) / static_cast<float>(image.width() - 1));
            image.pixel(x, y) = oklab_to_linear(glm::mix(color1, color2, static_cast<float>(x) / static_cast<float>(image.width() - 1))); 
        }
    }

}

// Fractale de Mandelbrot
void mandelbrot_fractal(sil::Image&image){

    glm::vec3 black {0, 0, 0};
    glm::vec3 white {1, 1, 1};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {

            std::complex<float> c{ static_cast<float> (x)/200 -1.75f, static_cast<float> (y-250)/200 }; // Définis le nombre z = 3 + 2*i
            std::complex<float> z{0, 0}; 

            for (int i = 0; i < 50; i++){
                z = z * z + c;
                if(std::abs(z) > 2){
                    image.pixel(x, y) = glm::vec3{static_cast<float>(i) / 50.f};
                    break;
                }
            }
            if (std::abs(z) < 2){
                image.pixel(x, y) = white;
            }
        }
    }
}

// Tramage 
void dithering(sil::Image&image){
    const int bayer_n = 4;
    float bayer_matrix_4x4[][bayer_n] = {
        {    -0.5,       0,  -0.375,   0.125 },
        {    0.25,   -0.25,   0.375, - 0.125 },
        { -0.3125,  0.1875, -0.4375,  0.0625 },
        {  0.4375, -0.0625,  0.3125, -0.1875 },
    };
    
    for (int x{0}; x < image.width(); x++) {
        for (int y{0}; y < image.height(); y++) {
            float bright = brightness(image.pixel(x, y));
            float threshold = bayer_matrix_4x4[y % bayer_n][x % bayer_n];

            if(bright + threshold > 0.5){
                image.pixel(x, y) = {1, 1, 1};
            }else{
                image.pixel(x, y) = {0, 0, 0};
            }
            
        }
    }
}

// test tramage couleur 
void dithering_color(sil::Image&image){
    const int bayer_n = 4;
    float bayer_matrix_4x4[][bayer_n] = {
        {    -0.5,       0,  -0.375,   0.125 },
        {    0.25,   -0.25,   0.375, - 0.125 },
        { -0.3125,  0.1875, -0.4375,  0.0625 },
        {  0.4375, -0.0625,  0.3125, -0.1875 },
    };
    
    for (int x{0}; x < image.width(); x++) {
        for (int y{0}; y < image.height(); y++) {
            float bright = brightness(image.pixel(x, y));
            float threshold = bayer_matrix_4x4[y % bayer_n][x % bayer_n];

            if(bright + threshold > 0.5){
                image.pixel(x, y) = {0, 0, 1};
                image.pixel(x, y) = {1, 0, 0};
            }else{
                image.pixel(x, y) = {0, 1, 0};
            }
            
        }
    }
}

// Normalisation de l'histogramme
void normalizing_histogram(sil::Image&image){
    
    float darkest = 1.f;
    float whitest = 0.f;
    for (int x{0}; x < image.width(); x++) {
        for (int y{0}; y < image.height(); y++) {

            glm::vec3 &pixel = image.pixel(x, y);
            float lum = brightness(pixel);
            if(lum < darkest){
                // si lum est + sombre que darkest, alors on remplace darkesst par lum
                darkest = lum;
            }else if (lum > whitest){
                whitest = lum;

            }else{}
            float normalizedLum = (lum - darkest) / (whitest - darkest);
            pixel = pixel * (normalizedLum / lum);


        
        }
    }
    std::cout << darkest << std::endl;
    std::cout << whitest << std::endl;

}

// Vortex 
void vortex(sil::Image &image){
    sil::Image original_image = image;

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            glm::vec2 current_point{x, y};
            glm::vec2 center_of_rotation{image.width()/2, image.height()/2};

            float distance = glm::distance(current_point, center_of_rotation);

            float angle = 45.f * (distance / glm::length(glm::vec2(image.width(), image.height())));

            glm::vec2 rotated_point = glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{current_point - center_of_rotation, 0.f}} + center_of_rotation;

            int rotated_x = static_cast<int>(std::round(rotated_point.x));
            int rotated_y = static_cast<int>(std::round(rotated_point.y));

            if (rotated_x >= 0 && rotated_x < image.width() && rotated_y >= 0 && rotated_y < image.height()) {
                image.pixel(x, y) = original_image.pixel(rotated_x, rotated_y);
            } else {
                image.pixel(x, y) = {0, 0, 0};
            }
        }
    }
}

// Convolution 
void convolution(sil::Image &image) {
    int kernel_size = 15;
    float sigma = 25.f;
    int half_size = kernel_size / 2;
    std::vector<std::vector<float>> kernel(kernel_size, std::vector<float>(kernel_size, 0.f));
    // float sum = 0.0;
    kernel = {
        {-1.f, -1.f, -1.f},
        {-1.f, 8.f, -1.f},
        {-1.f, -1.f, -1.f},
    };

    // for (int i = -half_size; i <= half_size; i++) {
    //     for (int j = -half_size; j <= half_size; j++) {
    //         float value = std::exp(-(i * i + j * j) / (2 * sigma * sigma));
    //         kernel[i + half_size][j + half_size] = value;
    //         sum += value;
    //     }
    // }

    // for (int i = 0; i < kernel_size; i++) {
    //     for (int j = 0; j < kernel_size; j++) {
    //         kernel[i][j] /= sum;
    //     }
    // }

    sil::Image blurred_image = image;

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            glm::vec3 color_sum(0.0f);

            for (int i = -half_size; i <= half_size; i++) {
                for (int j = -half_size; j <= half_size; j++) {
                    int neighbor_x = x + i;
                    int neighbor_y = y + j;

                    if (neighbor_x >= 0 && neighbor_x < image.width() &&
                        neighbor_y >= 0 && neighbor_y < image.height()) {

                        glm::vec3 neighbor_color = blurred_image.pixel(neighbor_x, neighbor_y);
                        color_sum += neighbor_color * kernel[i + half_size][j + half_size];
                    }
                }
            }

            image.pixel(x, y) = color_sum;
        }
    }
}




int main()
{
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     green_only(image); // Utilise la fonction pour modifier l'image
    //     image.save("output/green_only.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     channels_swap(image); // Utilise la fonction pour modifier l'image
    //     image.save("output/channels_swap.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     black_white(image); // Utilise la fonction pour modifier l'image
    //     image.save("output/black_white.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     negatif(image); // Utilise la fonction pour modifier l'image
    //     image.save("output/negatif.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{300, 200}; // Lis l'image
    //     gradiant(image); // Utilise la fonction pour modifier l'image
    //     image.save("output/gradiant.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     mirror(image); // Utilise la fonction pour modifier l'image
    //     image.save("output/mirror.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     noise(image); // Utilise la fonction pour modifier l'image
    //     image.save("output/noise.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     rotating(image); 
    //     image.save("output/rotating.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     rgb_split(image); 
    //     image.save("output/rgb_split2.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/photo.jpg"};
    //     light_luminosity(image); 
    //     image.save("output/light_luminosity.jpg"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/photo.jpg"};
    //     dark_Luminosity(image); 
    //     image.save("output/dark_luminosity.jpg"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{500, 500}; // Lis l'image
    //     disk(image); // Utilise la fonction pour modifier l'image
    //     image.save("output/disk.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{500, 500}; // Lis l'image
    //     circle(image); // Utilise la fonction pour modifier l'image
    //     image.save("output/circle.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{500, 500}; // Lis l'image
    //     animation(image); // Utilise la fonction pour modifier l'image
    // }
    // {
    //     sil::Image image{500, 500}; // Lis l'image
    //     animation_bonus(image); // Utilise la fonction pour modifier l'image
    // }
    // {
    //     sil::Image image{500, 500}; // Lis l'image
    //     rosace(image); // Utilise la fonction pour modifier l'image
    //     image.save("output/rosace.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     mosaic(image); 
    //     image.save("output/mosaic.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     mosaic_mirror(image); 
    //     image.save("output/mosaic_mirror.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     glitch(image); 
    //     image.save("output/glitch.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     pixel_sorting(image); 
    //     image.save("output/pixel_sorting.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{300, 200}; // Lis l'image
    //     gradiant_color(image, glm::vec3{1, 0.01, 0.6}, glm::vec3{0, 1, 0});
    //     image.save("output/gradiant_color.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{500, 500}; // Lis l'image
    //     mandelbrot_fractal(image);
    //     image.save("output/mandelbrot_fractal.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/photo.jpg"}; // Lis l'image
    //     dithering(image);
    //     image.save("output/dithering.jpg"); // Sauvegarde l'image
    // }
    {
        sil::Image image{"images/photo.jpg"}; // Lis l'image
        dithering_color(image);
        image.save("output/dithering_color3.jpg"); // Sauvegarde l'image
    }
    // {
    //     sil::Image image{"images/photo_faible_contraste.jpg"}; // Lis l'image
    //     normalizing_histogram(image);
    //     image.save("output/normalizing_histogram.jpg"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     vortex(image);
    //     image.save("output/vortex.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     convolution(image);
    //     image.save("output/convolution2.png"); // Sauvegarde l'image
    // }
    

}