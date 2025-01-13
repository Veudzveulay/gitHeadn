#include <iostream>
#include "GestionnaireDeContacts.h"

void afficherMenu() {
    std::cout << "\n--- Gestionnaire de Contacts ---\n";
    std::cout << "1. Ajouter un contact\n";
    std::cout << "2. Afficher tous les contacts\n";
    std::cout << "3. Rechercher un contact\n";
    std::cout << "4. Modifier un contact\n";
    std::cout << "5. Supprimer un contact\n";
    std::cout << "6. Trier les contacts\n";
    std::cout << "7. Exporter les contacts en CSV\n";
    std::cout << "0. Quitter\n";
    std::cout << "Choisissez une option : ";
}

int main() {
    GestionnaireDeContacts gestionnaire; 
    std::string fichier = "contacts.txt";

    // Chargement automatique des contacts au démarrage
    gestionnaire.charger(fichier);

    int choix;
    do {
        afficherMenu();
        std::cin >> choix;
        std::cin.ignore();

        switch (choix) {
            case 1: {
                std::string nom, prenom, telephone, email;

                std::cout << "Nom: ";
                std::getline(std::cin, nom);

                std::cout << "Prenom: ";
                std::getline(std::cin, prenom);

                // Validation du téléphone
                do {
                    std::cout << "Telephone: ";
                    std::getline(std::cin, telephone);
                    if (!gestionnaire.validerTelephone(telephone)) { 
                        std::cout << "Erreur : Format de telephone invalide. Entrez un numero valide (ex : +123456789).\n";
                    }
                } while (!gestionnaire.validerTelephone(telephone));

                // Validation de l'email
                do {
                    std::cout << "Email: ";
                    std::getline(std::cin, email);
                    if (!gestionnaire.validerEmail(email)) { 
                        std::cout << "Erreur : Format d'email invalide. Entrez une adresse valide (ex : exemple@test.com).\n";
                    }
                } while (!gestionnaire.validerEmail(email));

                gestionnaire.ajouterContact(nom, prenom, telephone, email);
                break;
            }

            case 2:
                gestionnaire.afficherContacts();
                break;

            case 3: {
                std::string critere;
                std::cout << "Entrez le nom, le numero de telephone ou l'ID à rechercher : ";
                std::getline(std::cin, critere);
                gestionnaire.rechercherContact(critere);
                break;
            }

            case 4: {
                std::string id;
                std::cout << "Entrez l'ID du contact à modifier : ";
                std::getline(std::cin, id);
                gestionnaire.modifierContact(id);
                break;
            }

            case 5: {
                std::string id;
                std::cout << "Entrez l'ID du contact à supprimer : ";
                std::getline(std::cin, id);
                gestionnaire.supprimerContact(id);
                break;
            }

            case 6: {
                std::string critere;
                bool ascendant;
                std::cout << "Critère de tri (nom, prenom, email) : ";
                std::getline(std::cin, critere);
                std::cout << "Ordre (1 pour ascendant, 0 pour descendant) : ";
                std::cin >> ascendant;
                std::cin.ignore();

                gestionnaire.trierContacts(critere, ascendant);
                break;
            }

            case 7: {
                std::string fichierCSV;
                std::cout << "Entrez le nom du fichier CSV (par exemple : contacts.csv) : ";
                std::getline(std::cin, fichierCSV);
                gestionnaire.exporterEnCSV(fichierCSV);
                break;
            }

            case 0:
                std::cout << "Au revoir !\n";
                break;

            default:
                std::cout << "Option invalide, veuillez reessayer.\n";
                break;
        }
    } while (choix != 0);

    return 0;
}