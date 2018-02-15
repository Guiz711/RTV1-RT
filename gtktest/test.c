#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc,char **argv)
{
	GtkBuilder      *builder; 
    GtkWidget       *window;
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "RT_menu.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_menu"));
    gtk_builder_connect_signals(builder, NULL);
 
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}

void on_window_main_destroy()
{
    gtk_main_quit();
}

void add_settingsmenu()
{
	GtkBuilder      *builder; 
    GtkWidget       *win;
 
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "RT_menu.glade", NULL);
 
    win = GTK_WIDGET(gtk_builder_get_object(builder, "settings_menu"));
    gtk_builder_connect_signals(builder, NULL);
 
    // g_object_unref(builder);
 
    gtk_widget_show(win);                
    // gtk_main();
 
}
// // gtk_widget_action()

// //widget = widget sur lequel on travaill. ext : window
// //action = fonction : ex : set_title

// #include <stdlib.h>
// #include <gtk/gtk.h>

// int main(int argc, char **argv)
// {
//     /* Initialisation de GTK+ */
//     gtk_init(&argc, &argv);
//     GtkWidget *MainWindow;
//     *MainWindow = NULL;

//     GtkWidget* gtk_window_new(GtkWindowType /*type*/GTK_WINDOW_TOPLEVEL); 
//     //Deux types différents : GTK_WINDOW_TOPLEVEL : Une fenêtre normale.
// 	//GTK_WINDOW_POPUP : Une fenêtre sans bordure (ne pas utiliser, sauf cas particuliers).

// 	//Afficher un widget : void gtk_widget_show(GtkWidget *widget);
// 	//Ou pour les afficher tous : void gtk_widget_show_all(GtkWidget *widget);
// 	g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
// 	gtk_main();

// 	//Le titre :
// 	//void gtk_window_set_title(GtkWindow *window, const gchar *title); => fonction pour définir un titre;
// 	//gtk_window_set_title(GTK_WINDOW(MainWindow), "Fenetre de zer0"); => Utilisation de la macro GTK_WINDOW;
// 	//const gchar* gtk_window_get_title(GtkWindow *window); => Récupere la chaine titre, en gchar !
	
// 	//La taille (par défaut):
// 	//void gtk_window_set_default_size(GtkWindow *window, gint width, gint height);  => fonction pour définir taille de la fenetre;
// 	//void gtk_window_get_default_size (GtkWindow *window, gint *width, gint *height); : Recupérer la taille par défaut : On donne deux pointeurs gint (int de la Glib, comme le gchar !) et Gtk les modifie pour vous donner la taille.
	
// 	//La taille actuelle : 
// 	//void gtk_window_resize (GtkWindow *window, gint width, gint height); => Pour la définir;
// 	//void gtk_window_get_size (GtkWindow *window, gint *width, gint *height); => Pour la récupérer;
	
// 	//Positionnement :
// 	//GTK_WIN_POS_NONE : Position aléatoire.
// 	//GTK_WIN_POS_MOUSE : Position de la souris au moment de l'appel.
// 	//GTK_WIN_POS_CENTER : Fenêtre centrée.
// 	//GTK_WIN_POS_CENTER_ALWAYS : Toujours centrée, non déplaçable.
// 	//GTK_WIN_POS_CENTER_ON_PARENT : Centrée par rapport à la fenêtre parente.
// 	//Ci-dessus les différentes possibilités pour void gtk_window_set_position(GtkWindow *window, GtkWindowPosition position);
// 	//Sinon avec x et y : void gtk_window_move(GtkWindow *window, gint x, gint y);
// 	//Récup la pos : void gtk_window_get_position(GtkWindow *window, gint *root_x, gint *root_y);

// 	//L'icone : 
// 	//gboolean gtk_window_set_icon_from_file   (GtkWindow *window, const gchar *filename, GError **err); a partir d'un fichier
// 	//ou bien avec gtk_window_set_icon 
// 	//Récup : GdkPixbuf * gtk_window_get_icon (GtkWindow *window);
// 	//BUFFER DE PIXEL;

// 	//Iconifier (réduire la fenetre):
// 	//void gtk_window_iconify (GtkWindow *window);
// 	//Restaurer :
// 	//void gtk_window_deiconify (GtkWindow *window);

// 	//Maximiser :
// 	//void gtk_window_maximize (GtkWindow *window);
// 	//Restaurer :
// 	//void gtk_window_unmaximize (GtkWindow *window);

// 	//Bouton "fermer"
// 	//Définir l'état du bouton fermer : Donnez TRUE pour activer le bouton, FALSE pour le désactiver.
// 	//void gtk_window_set_deletable (GtkWindow *window, gboolean setting);
// 	//Connaître l'état : La fonction renvoie TRUE si le bouton est actif, FALSE sinon.
// 	//gboolean gtk_window_get_deletable (GtkWindow *window);

// 	//Les bordures
// 	//Définir l'épaisseur des bordures : Donnez la fenêtre et l'épaisseur des bordures en pixels, dans l'ordre gauche, haut, droite, bas.
// 	//void gtk_window_set_frame_dimensions (GtkWindow *window, gint left, gint top, gint right, gint bottom);
// 	//Connaître l'épaisseur : Mêmes paramètres, mais en pointeurs pour que vous puissiez y avoir accès.
// 	//void gtk_window_get_frame_dimensions (GtkWindow *window, gint *left, gint *top, gint *right, gint *bottom);

// 	//Les labels : le texte dans les fenetres
// 	//Déclarer : GtkWidget* label = NULL;
// 	//Initialiser : GtkWidget* gtk_label_new (const gchar *str);
// 	//Le rajouter dans la fenetre : void gtk_container_add (GtkContainer *container, GtkWidget *widget); MACRO POUR GtkContainer *container => GTK_CONTAINER();
// 	//container : Le nom du widget qui contiendra notre label. Dans notre cas, c'est la fenêtre.
// 	//widget : Le nom du widget à ajouter. Ici, nous rajouterons notre label
// 	//________________//
// 	//Récuperer un label : const gchar* gtk_label_get_label (GtkLabel *label); => MACRO : GTK_LABEL()
// 	//Modifier un label : void gtk_label_set_label (GtkLabel *label, const gchar *str);
// 	//_______________//
// 	//L'alignement : void gtk_label_set_justify (GtkLabel *label, GtkJustification jtype);
// 	//jtype : GTK_JUSTIFY_LEFT -> Aligne le texte à gauche (par défaut).
// 	//GTK_JUSTIFY_CENTER -> Aligne le texte au centre.
// 	//GTK_JUSTIFY_RIGHT -> Aligne le texte à droite.
// 	//GTK_JUSTIFY_FILL -> Aligne le texte à droite et à gauche à la fois. Le texte est alors justifié.
// 	//_____________//
// 	//Formatage du texte : 
// 	//Avec balises simples : <b> -> Mets le texte en gras
// 	//<i> -> Mets le texte en italique
// 	//<u> -> Souligne le texte
// 	//<s> -> Barre le texte
// 	//<sub> -> Mets le texte en indice
// 	//<big> -> Rend la police relativement plus grande (+1)
// 	//<small> -> Rend la police relativement plus petite (-1)
// 	//<tt> -> Met le texte en télétype
// 	//____________________//
// 	//Avec Span : <span attribut1="valeur" attribut2="valeur">...</span>
// 	//font_family -> Nom de la police de caractère
// 	//face -> C'est un autre attribut qui définit la police
// 	//size -> C'est la taille de la police. On peut aussi utiliser 'xx-small', 'x-small', 'small', 'medium', 'large', 'x-large', 'xx-large' ou une valeur numérique.
// 	//style -> Définit le style des caractères : 'normal', 'oblique' ou 'italic'
// 	//weight -> Définit le ton du gras du caractère : 'ultralight', 'light', 'normal', 'bold', 'ultrabold', 'heavy' ou une valeur numérique.
// 	//variant -> Met le texte en petites majuscules (smallcaps) ou en normal (normal, valeur par défaut).
// 	//stretch -> définit l'espacement des lettres: 'ultracondensed', 'extracondensed', 'condensed', 'semicondensed', 'normal', 'semiexpanded', 'expanded', 'extraexpanded' ou 'ultraexpanded'.
// 	//foreground -> Définit la couleur du texte en valeur hexadécimale
// 	//background -> Définit la couleur du fond texte en valeur hexadécimale
// 	//underline -> Définit le soulignement du texte: 'single', 'double', 'low' ou 'none'.
// 	//underline_color -> Définit la couleur du soulignement en valeur hexadécimale
// 	//rise -> Définit l'élévation du texte (en indice ou exposant) en valeur décimal (les valeurs négatives sont possibles, pour mettre notamment notre texte en indice)
// 	//strikethrough -> Pour barrer son texte. La valeur doit être soit TRUE ou FALSE
// 	//strikethrough_color -> Définit la couleur de la ligne qui barre le texte en valeur hexadécimale
// 	//fallback -> Si votre caractère n'est pas disponible dans le police choisie, alors une police qui contient ce caractère sera choisi. Elle est activée par défaut.
// 	//lang -> Définit la langue du texte
// 	//____________//
// 	//Si on use UTF-8 on doit intégrer nos balises a notre fonction de conversion
// 	//g_locale_to_utf8("tout le span");
// 	//void gtk_label_set_use_markup (GtkLabel *label, gboolean setting); mettre TRUE a la place de setting;
// 	//Sans UTF8 : 
// 	//void gtk_label_set_markup (GtkLabel *label, const gchar *str);

// 	//Les évenements : les signaux;
// 	//Gérer un event : g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK( mafonction ), NULL);
// 	//Prototype est : gulong g_signal_connect(gpointer *object, const gchar *name, GCallback func, gpointer func_data );
// 	//On peut dire que : Quand object émet le signal name, GTK+ appelle la fonction func avec les paramètres object et data. Donc à ce moment là, GTK génère cet appel et l'exécute : func(object, data);
// 	//Proto de la fonction func : void mafonction(GtkWidget *widget, gpointer data);

// 	//La boucle principale :
// 	//void gtk_main(void);
// 	//void gtk_main_quit(void);


 




// 	return EXIT_SUCCESS;
// }

// EXEMPLE 1 : 
// EXEMPLE 1 : 
// EXEMPLE 1 : 
// EXEMPLE 1 : 


// #include <time.h>
// #include <stdlib.h>
// #include <gtk/gtk.h>

// void Pause(int Temps);

// int main(int argc,char **argv)
// {
//     GtkWidget* pWindow;
//     const gchar* sTitre;
//     gint sLargeur;
//     gint sHauteur;
//     gint sPosition_y;
//     gint sPosition_x;
//     int icone;
//     gtk_init(&argc,&argv);
//     pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//     /* Personnalisation de la Fenêtre */ 
//     // Titre
//     gtk_window_set_title(GTK_WINDOW(pWindow), "GTK+ 2.10");
//     // Taille
//     gtk_window_set_default_size(GTK_WINDOW(pWindow), 260, 40);
//     // Position
//     gtk_window_set_position(GTK_WINDOW (pWindow), GTK_WIN_POS_CENTER);
//     // Icône
//     icone = gtk_window_set_icon_from_file(GTK_WINDOW(pWindow), "icone.ico", NULL);
//     g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
//     /* Récupération des Informations sur la Fenêtre */
//     // Titre
//     sTitre = gtk_window_get_title(GTK_WINDOW(pWindow));
//     // Taille
//     gtk_window_get_default_size(GTK_WINDOW(pWindow), &sLargeur, &sHauteur);
//     // Position
//     gtk_window_get_position(GTK_WINDOW(pWindow), &sPosition_x, &sPosition_y);
//     /* Affichage des Informations */
//     // On pourrait afficher ces informations dans la Fenêtre grâce à un Label mais vous les verrez dans le prochain Chapitre donc on affiche les données dans la Console
//     printf("\n-------\nFenetre\n------- \n \nTitre: %s \nTaille: %d x %d \nPosition: %dy %dx\nIcone: ", sTitre, sLargeur, sHauteur, sPosition_y, sPosition_x);
//     // Icône
//     if (icone == 1) // Si l'icône est Chargée
//        printf("Charge! \n");
//     else if (icone == 0) // Si l'icône n'est pas Chargée (impossible de l'ouvrir)
//        printf("Impossible de Charger l'icone... \n");
//     Pause(3);
//     gtk_widget_show_all(pWindow);
//     /* Modification de la Fenêtre */ 
//     Pause(1);
//     printf("\n \n------------\nModification\n------------\n");
//     sPosition_y = 200;
//     sPosition_x = 200;
//     // Position
//     gtk_window_move(GTK_WINDOW(pWindow), sPosition_x, sPosition_y);
//     printf("\nNouveau positionnement: %d x %d", sPosition_y, sPosition_x);
//     Pause(1);
//     sLargeur = 460;
//     sHauteur = 240;
// 	// Taille
//     gtk_window_resize(GTK_WINDOW(pWindow), sLargeur, sHauteur); // On verra le changement de Taille de la Fenêtre lorsqu'on la Restaurera
//     printf("\nNouvelle taille: %d x %d", sHauteur, sLargeur);
//     Pause(1);
//     // Maximiser
//     gtk_window_maximize(GTK_WINDOW(pWindow));
//     printf("\nMaximiser");
//     Pause(1);
//     // Restaurer
//     gtk_window_unmaximize(GTK_WINDOW(pWindow)); // On voie la Nouvelle Taille de la Fenêtre => Elle n'est plus petite comme avant
//     printf("\nRestaurer");
//     gtk_main();
//     return EXIT_SUCCESS;
// }

// void Pause(int Temps)
// {
//     int T1, T2;
//      T1 = time(NULL);
//      do
//      {
//           T2 = time(NULL);
//      }     
//      while(T2-T1 != Temps);
// }


// EXEMPLE 2 : 
// EXEMPLE 2 : 
// EXEMPLE 2 : 
// // EXEMPLE 2 :

// int main ()
// {
// 	// GtkWidget* Fenetre = NULL;
//     // GtkWidget* Label = NULL;
//     // gchar* TexteConverti = NULL;
//     // gtk_init(&argc, &argv);
//     // Fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);  // Définition de la fenêtre
//     // gtk_window_set_title(GTK_WINDOW(Fenetre), "Le texte avec les labels"); // Titre de la fenêtre
//     // gtk_window_set_default_size(GTK_WINDOW(Fenetre), 300, 100); // Taille de la fenêtre
//     // TexteConverti = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#73b5ff\" size=\"xx-large\"><b>Le site du ZérTo</b></span>\n <span face=\"Verdana\" foreground=\"#39b500\" size=\"x-large\">Le tuto GTK</span>\n", -1, NULL, NULL, NULL);  //Convertion du texte avec les balises
//     // Label=gtk_label_new(TexteConverti); // Application de la convertion à notre label
//     // g_free(TexteConverti); // Libération de la mémoire
//     // gtk_label_set_use_markup(GTK_LABEL(Label), TRUE); // On dit que l'on utilise les balises pango
//     // gtk_label_set_justify(GTK_LABEL(Label), GTK_JUSTIFY_CENTER); // On centre notre texte
//     // gtk_container_add(GTK_CONTAINER(Fenetre), Label);  // On ajoute le label a l'interieur de 'Fenetre'
//     // gtk_widget_show_all(Fenetre); // On affiche 'Fenetre' et tout ce qu'il contient
//     // g_signal_connect(G_OBJECT(Fenetre), "delete-event", G_CALLBACK(gtk_main_quit), NULL); // Je ne commente pas cette fonction, vous la verrez dans le chapitre suivant.
//     // gtk_main();
//     // return EXIT_SUCCESS;
// }


