# 🐣 S1 | Prog: Workshop | Mini-rapport 

Cette semaine de workshop était destinée à apprendre à coder des effets sur images (traitement d'image) en c++. 
<br/>
Ce rapport va se présenter sous la forme suivante : 
- Le nom des exercices avec leur difficulté représentée sous la forme 🌟
- Le avant / après 
- Ainsi que des explications pour certains 



<details>
   <summary> Avant-propos </summary>

**Base commune** 

Chaque exercice se trouve dans mon fichier `main.cpp`, représenté par une fonction ``void``
Pour chaque exercice on utilise, comme base, deux boucles imbriquées :
```cpp
void nom_exercice(sil::Image& image){ // prend l'image par référence pour pouvoir la modifier 
    for (int x{0}; x < image.width(); x++)
{
    // parcours la largeur de l'image 

    for (int y{0}; y < image.height(); y++)
    {
        // parcours la hauteur de l'image 
        ...
    }
}
}
```
Ensemble ces deux boucles permettent de parcourir chaque pixel de l'image en utilisant les coordonnées (x, y). 
<br/>

```cpp
int main (){
    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        green_only(image); // Utilise la fonction pour modifier l'image
        image.save("output/green_only.png"); // Sauvegarde l'image
    }
}
```
</details>

_______________________________________________________

Sommaire des exercices : 
- [🐣 S1 | Prog: Workshop | Mini-rapport](#-s1--prog-workshop--mini-rapport)
  - [🌟 Ne garder que le vert](#-ne-garder-que-le-vert)
  - [🌟 Échanger les canaux](#-échanger-les-canaux)
  - [🌟 Noir \& Blanc](#-noir--blanc)
  - [🌟 Négatif](#-négatif)
  - [🌟 Dégradé](#-dégradé)
  - [🌟🌟 Miroir](#-miroir)
  - [🌟🌟 Image bruitée](#-image-bruitée)
  - [🌟🌟 Rotation de 90°](#-rotation-de-90)
  - [🌟🌟 RGB split](#-rgb-split)
  - [🌟🌟 Luminosité](#-luminosité)
  - [🌟🌟(🌟) Disque](#-disque)
    - [🌟 Cercle](#-cercle)
    - [🌟🌟 Animation](#-animation)
    - [🌟🌟🌟 Rosace](#-rosace)
  - [🌟🌟 Mosaïque](#-mosaïque)
    - [🌟🌟🌟🌟 Mosaïque mirroir](#-mosaïque-mirroir)
  - [🌟🌟🌟 Glitch](#-glitch)
  - [🌟🌟🌟 Tri de pixel](#-tri-de-pixel)
  - [🌟🌟🌟 Dégradés dans l'espace de couleur Lab](#-dégradés-dans-lespace-de-couleur-lab)
  - [🌟🌟🌟(🌟) Fractale de Mandelbrot](#-fractale-de-mandelbrot)
  - [🌟🌟🌟(🌟) Tramage](#-tramage)
  - [🌟🌟🌟(🌟) Normalisation de l'histogramme](#-normalisation-de-lhistogramme)
  - [🌟🌟🌟🌟 Vortex](#-vortex)
  - [🌟🌟🌟🌟 Convolutions](#-convolutions)
    - [🌟 Netteté, Contours etc.](#-netteté-contours-etc)
  - [🌟 Bonus 🌟 ( ' u ' )](#-bonus----u--)

<br/>

__________________________________
## 🌟 Ne garder que le vert
| ![logo.png](/images/logo.png)  | ![green_only.png](/output/green_only.png)  |
|----|----|
| *Image originale* | *Après* |

```cpp
    image.pixel(x, y).r = 0;
    image.pixel(x, y).b = 0;
```
- ``image.pixel(x, y)`` accède au pixel au coordonées (x, y) de l'image 
- ``.r`` et ``.b`` correspondent, respectivement, aux composantes rouge et bleue du pixel. Sachant que 1 est la valeur maximale, en leur assignant 0, on enlève ces composantes au pixel en ne lui laissant que du vert.
  <br/>
______________________________
## 🌟 Échanger les canaux 
| ![logo.png](/images/logo.png)  | ![channels_swap.png](/output/channels_swap.png)  |
|----|----|
| *Image originale* | *Après* |

```cpp
    std::swap(image.pixel(x,y).r, image.pixel(x,y).b);
```

- ``std::swap`` permet d'échanger les valeurs des canaux rouge et bleu. 
<br/>
________________________________

## 🌟 Noir & Blanc
| ![logo.png](/images/logo.png)  | ![black_white.png](/output/black_white.png)  |
|----|----|
| *Image originale* | *Après* |

________________________________

## 🌟 Négatif 
| ![logo.png](/images/logo.png)  | ![negatif.png](/output/negatif.png)  |
|----|----|
| *Image originale* | *Après* |

```cpp
    glm::vec3 &pixel = image.pixel(x, y);
    pixel.r = 1.0f - pixel.r;
    pixel.g = 1.0f - pixel.g;
    pixel.b = 1.0f - pixel.b;
    // 
```

- ``pixel.r = 1.0f - pixel.r`` : Chaque composante de couleur est inversée en soustrayant sa valeur à 1, transformant les zones claires en foncées et vice versa pour créer un effet de négatif.
<br/>
________________________________

## 🌟 Dégradé 
![gradiant.png](/output/gradiant.png)

```cpp
    image.pixel(x, y) = glm::vec3{static_cast<float>(x) / static_cast<float>(image.width() - 1)};
    // Chaque pixel est coloré en fonction de sa position horizontale, allant du noir à gauche au blanc à droite, en créant un dégradé en niveaux de gris.
```
<br/>

________________________________

## 🌟🌟 Miroir
| ![logo.png](/images/logo.png)  | ![mirror.png](/output/mirror.png)  |
|----|----|
| *Image originale* | *Après* |

- ``std::swap(image.pixel(x, y), image.pixel(image.width() - (x + 1), y))`` : Cette ligne échange un pixel de la moitié gauche de l'image avec son pixel symétrique dans la moitié droite pour créer un effet miroir horizontal.

<br/>

________________________________
## 🌟🌟 Image bruitée 
| ![logo.png](/images/logo.png)  | ![noise.png](/output/noise.png)  |
|----|----|
| *Image originale* | *Après* |

```cpp
    if(true_with_probability(0.3f)){ // 
        image.pixel(x, y).r = random_float(0, 1);
        image.pixel(x, y).g = random_float(0, 1);
        image.pixel(x, y).b = random_float(0, 1);
        // Cette portion de code signifie que, avec une probabilité de 30 %, 
        // la couleur d'un pixel donné est remplacée par une nouvelle couleur générée aléatoirement
    }
```
- ``true_with_probability(0.3f)`` : Vérifie si un événement aléatoire se produit avec 30 % de chance.
- S'il est vrai : 
  - ``random_float(0, 1)`` : génère une valeur aléatoire entre 0 et 1 pour chaque composante de couleur (rouge, vert, bleu).
  - Ces valeurs sont attribuées au pixel, changeant sa couleur en une teinte aléatoire.
<br/>
________________________________

## 🌟🌟 Rotation de 90°
| ![logo.png](/images/logo.png)  | ![rotating.png](/output/rotating.png)  |
|----|----|
| *Image originale* | *Après* |

```cpp
void rotating(sil::Image&image){
    int new_width = image.height(); // La largeur de l'image devient sa nouvelle hauteur.
    int new_height = image.width(); //La hauteur de l'image devient sa nouvelle largeur.
    
    sil::Image new_image{new_width, new_height}; // Une nouvelle image vide est créée avec les dimensions inversées.
    for (int y{0}; y < new_image.height(); y++)
    {
        for (int x{0}; x < new_image.width(); x++)
        {
           new_image.pixel(x, y) =image.pixel (image.width() - 1 - y, x); // Inverse l'axe horizontal pour "faire pivoter" l'image.
        }
    } 
    image = new_image; //L'image originale est remplacée par la nouvelle image pivotée.
}
```
<br/>

________________________________

## 🌟🌟 RGB split 
| ![logo.png](/images/logo.png)  | ![rgb_split2.png](/output/rgb_split2.png)  |
|----|----|
| *Image originale* | *Après* |

```cpp
if(x >= 30) {
    image_split.pixel(x, y).r = image.pixel(x - 30, y).r;
}
if (x < image.width() - 31) {
    image_split.pixel(x, y).b = image.pixel(x + 30, y).b;
} 
    image_split.pixel(x, y).g = image.pixel(x, y).g; // Le canal vert du pixel reste inchangé
```
- Le décalage des couleurs rouge et bleu consiste à déplacer le canal rouge vers la gauche de 30 pixels et le canal bleu vers la droite de 30 pixels, tout en laissant le canal vert inchangé, créant ainsi un effet de séparation des couleurs.

Voici un fail que j'avais fait : 
![rgb_split.png](/output/rgb_split.png)
Le problème avec celui-ci, c'est que j'avais gardé en arrière-plan l'image original. Il faut donc bien rajouté à la fin ``image = image_split`` qui reprend l'image et qui l'a remplace par la nouvelle image transformée.
<br/>

 ________________________________

## 🌟🌟 Luminosité 
| ![photo.jpg](/images/photo.jpg)  | ![light_luminosity.jpg](/output/light_luminosity.jpg)  |![dark_luminosity.jpg](/output/dark_luminosity.jpg)  |
|---|----|----|
| Image originale | Après éclaircissement | Après assombrissement |

<br/>

Pour réaliser cet exercice, on recherche des fonctions qui correspondent à ces courbes. 
- La courbe bleue diminue tous les nombres entre 0 et 1 = assombrissement 
- la courbe verte les augmente = éclaircissement
<br/>

![courbe_luminosity.png](/images/courbe_luminosity.png)

<br/>

**Éclaircissement**
La fonction correpondante est la racine carrée √a
```cpp
image.pixel(x, y).r = std::sqrt(image.pixel(x, y).r);
image.pixel(x, y).g = std::sqrt(image.pixel(x, y).g);
image.pixel(x, y).b = std::sqrt(image.pixel(x, y).b);
// Pour chaque pixel à la position (x, y), la racine carrée est appliquée à chaque composant de couleur (rouge, vert et bleu)
``` 
- La fonction ``std::sqrt()`` prend la valeur de chaque composant de couleur et applique la racine carrée, ce qui modifie les couleurs en augmentant les valeurs proches de zéro et en réduisant les valeurs proches de 1.
- Cela réduit l'intensité des couleurs. Les couleurs plus sombres (avec des valeurs faibles) deviennent plus claires, tandis que les couleurs déjà claires sont moins modifiées, éclaircissant ainsi l'image.

<br/>

**Assombrissement**
La fonction correpondante est la puissance au carrée ²

```cpp
image.pixel(x, y).r = std::pow(image.pixel(x, y).r, 2);
image.pixel(x, y).g = std::pow(image.pixel(x, y).g, 2);
image.pixel(x, y).b = std::pow(image.pixel(x, y).b, 2);
```
- ``std::pow()`` élève les composantes à la puissance de 2. Cela augmente l'intensité des couleurs si leur valeur est proche de zéro et l'intensifie davantage si elle est déjà élevée.
- Cela donne un effet plus saturer à l'image.

<br/>

________________________________

## 🌟🌟(🌟) Disque 
![disk.png](/output/disk.png)
Pour réaliser un disque, nous allons créer une nouvelle image de 500x500. Tout d'abord on va rechercher à centrer le disque :
```cpp 
    int a{image.width()/2};
    int b{image.height()/2};
    int r{100};
```
- ``a`` et ``b`` coorespondent aux coordonnées du centre de l'image. 
- ``r`` est le rayon du disque définit à 100 pixels.
```cpp 
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
```
Nous reprenons l'équation du disque = *(x−a)² + (y−b)² < r²*
Les conditions ci-dessus cherchent déterminer si un pixel se trouve à l'intérieur du cercle, ou non. 
- Si la somme des carrés des distances entre le pixel (x, y) et le centre du cercle est inférieure au carré du rayon, le pixel se trouve à l'intérieur du cercle et il est coloré en rouge.
- Sinon, le pixel se trouve à l'extérieur du cercle, et il est coloré en blanc.

<br/>

____________________________________

### 🌟 Cercle 
![circle.png](/output/circle.png)

<br/>

____________________________________
### 🌟🌟 Animation 
![animation_japon.gif](/output/animation_japon.gif)

Pour réaliser l'animation nous reprenons le code de notre disque en modifiant certains éléments. 
```cpp
    int a{0};
    int b{image.height()/2};
    int r{100};
```
- ``a`` correspond à la position horizontale. On l'initialise à 0 puisque l'on va déplacer notre disque sur l'axe horizontal. 

```cpp
while (a < 500)
    {
        a++; // La position horizontale du cercle (a) est incrémentée de 1, déplaçant le cercle vers la droite.
        //...
        image.save("output/anim/animation"+std::to_string(a)+".png");
    }        
```
- ``while (a < 500)`` : La boucle while incrémente la position horizontale du cercle (a) jusqu'à atteindre 500, faisant bouger le cercle de gauche à droite.
  
- ``image.save("output/anim/animation"+std::to_string(a)+".png")`` : À chaque étape, l'image est sauvegardée avec un nom unique, par exemple *animation1.png*, *animation2.png*, etc., dans le dossier output/anim (jusqu'à 500).

<br/>

_____________________________________
### 🌟🌟🌟 Rosace
![rosace.png](/output/rosace.png)

<br/>

_____________________________________
## 🌟🌟 Mosaïque 
![mosaic.png](/output/mosaic.png)
<br/>

_____________________________________
### 🌟🌟🌟🌟 Mosaïque mirroir 
![mosaic_mirror.png](/output/mosaic_mirror.png)
<br/>

________________________________

## 🌟🌟🌟 Glitch
| ![logo.png](/images/logo.png)  | ![glitch.png](/output/glitch.png)  |
|----|----|
| *Image originale* | *Après* |

<br/>

______________
## 🌟🌟🌟 Tri de pixel 
| ![logo.png](/images/logo.png)  | ![pixel_sorting.png](/output/pixel_sorting.png)  |
|----|----|
| *Image originale* | *Après* |

<br/>

________________________________
## 🌟🌟🌟 Dégradés dans l'espace de couleur Lab 
![gradiant_color.png](/output/gradiant_color.png)

<br/>

________________________________
## 🌟🌟🌟(🌟) Fractale de Mandelbrot 
![mandelbrot_fractal.png](/output/mandelbrot_fractal.png)

<br/>

________________________________
## 🌟🌟🌟(🌟) Tramage 
![dithering.jpg](/output/dithering.jpg)

<br/>

________________________________
## 🌟🌟🌟(🌟) Normalisation de l'histogramme 

| ![photo_faible_contraste.jpg](/images/photo_faible_contraste.jpg)  | ![normalizing_histogram.jpg](/output/normalizing_histogram.jpg)  |
|----|----|
| *Image originale* | *Après* |

<br/>


________________________________
## 🌟🌟🌟🌟 Vortex
| ![logo.png](/images/logo.png)  | ![vortex.png](/output/vortex.png)  |
|----|----|
| *Image originale* | *Après* |

<br/>

________________________________
## 🌟🌟🌟🌟 Convolutions 
| ![logo.png](/images/logo.png)  | ![convolution.png](/output/convolution.png)  |
|----|----|
| *Image originale* | *Après* |

</br>

**Après avoir réaliser convolution, pour réaliser la netteté, les contours etc ; Il y a juste à changer les valeurs du kernel.**
</br>

### 🌟 Netteté, Contours etc.
![convolution2.png](/output/convolution2.png)

<br/>


____________

## 🌟 Bonus 🌟 ( ' u ' )
Dans cette section, j'ai décidé de présenter ce que j'ai réalisé à partir de mes exercices préférés : Tramage et Animation.

**Tramage** 
J'aime beaucoup le rendu du Tramage sur les images alors j'ai repris exactement le même code ([🌟🌟🌟(🌟) Tramage](#-tramage)) mais en changeant les couleurs : 
```cpp
if(bright + threshold > 0.5){

    image.pixel(x, y) = {0, 0, 1};
    image.pixel(x, y) = {1, 0, 0};

    }else{
    
        image.pixel(x, y) = {0, 1, 0};
    }
    // code correspondant à la dernière image
```
<br/>

Mes différents tests : 

| ![dithering_color.jpg](/output/dithering_color.jpg)  | ![dithering_color2.jpg](/output/dithering_color2.jpg)  |
|----|----|

 
![dithering_color3.jpg](/output/dithering_color3.jpg)
- Pour cette image, j'ai voulu essayé de faire un mélange de couleur, mais ça n'a pas marché. A la place j'ai eu un résultat inattendu.

<br/>

J'ai aussi appliqué le Tramage sur d'autres images comme la fractale de Mandelbrot :

![dithering_test.jpg](/output/dithering_test.jpg)


__________
<br/>

**Animation** 
J'ai beaucoup aimé réalisé l'animation du disque en exportant 500 images. Ce qui m'a donné ce résultat : 
![animation_japon.gif](/output/animation_japon.gif)
Le fait d'avoir une animation très lente me faisait penser au temps qui passe. 
C'est alors que j'ai essayé de réalisé le temps d'une journée avec le soleil et le ciel. 
<br/>

**Étape 0 : le code**
Reprise du code de ([🌟🌟 Animation](#-animation))
</br>

**Étape 1 : le mouvement**
Dans un premier temps, je voulais changer la trajectoire de notre disque en lui faisant faire une trajectoire parabolique.
La fonction qui correspond à cette trajectoire est f(x)=-x²

```cpp
int b{300*(1-square((a-250.f)/250.f))};// b == center_y
```

**Étape 2 : le  "grossissement"**
```cpp

```

**Étape 3 : les couleurs**
```cpp
glm::vec3 color_sun{glm::mix(white, red, pourcentage)};
glm::vec3 color_sky{glm::mix(blue, bordeaux, pourcentage)};
```

**Étape 4 : le glow**
```cpp
else if (distance < r + 50)
    {
        float p2 = (distance - r) / 50;
        image.pixel(x, y)= glm::mix(color_sun, color_sky, p2 );
    }
```

**Résultat final :**

![animation_bonus_FINAL.gif](/output/animation_bonus_FINAL.gif)

*Inspiration* : [La lune de sang dans Zelda](https://www.youtube.com/watch?v=4KZsT_ZPXiI)