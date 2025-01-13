#ifndef GESTIONNAIRE_DE_CONTACTS_H
#define GESTIONNAIRE_DE_CONTACTS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <regex>
#include <random>
#include "Contact.h"

class GestionnaireDeContacts {
private:
    std::vector<Contact> contacts;
    std::string fichierSauvegarde = "contacts.txt";

    // Générer un ID unique
    std::string genererIdUnique() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(1000, 9999);
        return "C" + std::to_string(dis(gen));
    }

    // Sauvegarde automatique
    void sauvegardeAutomatique() {
        sauvegarder(fichierSauvegarde);
    }

public:

    // Valider un numéro de téléphone
    bool validerTelephone(const std::string& telephone) {
        std::regex pattern("^\\+?[0-9]{10,15}$");
        return std::regex_match(telephone, pattern);
    }

    // Valider un email
    bool validerEmail(const std::string& email) {
        std::regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
        return std::regex_match(email, pattern);
    }

    // Ajouter un contact
    void ajouterContact(const std::string& nom, const std::string& prenom, 
                    const std::string& telephone, const std::string& email) {
    if (!validerTelephone(telephone)) {
        std::cerr << "Numero de telephone invalide. Veuillez reessayer.\n";
        return;
    }
    if (!validerEmail(email)) {
        std::cerr << "Email invalide. Veuillez reessayer.\n";
        return;
    }
    std::string id = genererIdUnique();
    contacts.emplace_back(id, nom, prenom, telephone, email);
    std::cout << "Contact ajoute avec succes ! ID : " << id << '\n';
    sauvegardeAutomatique();
    }

    // Afficher tous les contacts
    void afficherContacts() const {
        if (contacts.empty()) {
            std::cout << "Aucun contact a afficher.\n";
            return;
        }
        for (const auto& contact : contacts) {
            contact.afficher();
        }
    }

    // Rechercher un contact
    void rechercherContact(const std::string& critere) const {
        bool trouve = false;
        for (const auto& contact : contacts) {
            if (contact.getNom() == critere || contact.getTelephone() == critere || contact.getId() == critere) {
                contact.afficher();
                trouve = true;
            }
        }
        if (!trouve) {
            std::cout << "Aucun contact trouve pour le critere : " << critere << '\n';
        }
    }

    // Modifier un contact
    void modifierContact(const std::string& id) {
        for (auto& contact : contacts) {
            if (contact.getId() == id) {
                std::string nouveauNom, nouveauPrenom, nouveauTelephone, nouveauEmail;

                std::cout << "Entrez les nouvelles informations pour le contact (laisser vide pour conserver les anciennes valeurs) :\n";
                std::cout << "Nom [" << contact.getNom() << "]: ";
                std::getline(std::cin, nouveauNom);
                if (!nouveauNom.empty()) contact.setNom(nouveauNom);

                std::cout << "Prenom [" << contact.getPrenom() << "]: ";
                std::getline(std::cin, nouveauPrenom);
                if (!nouveauPrenom.empty()) contact.setPrenom(nouveauPrenom);

                std::cout << "Telephone [" << contact.getTelephone() << "]: ";
                std::getline(std::cin, nouveauTelephone);
                if (!nouveauTelephone.empty()) {
                    if (validerTelephone(nouveauTelephone)) {
                        contact.setTelephone(nouveauTelephone);
                    } else {
                        std::cerr << "Numero de telephone invalide. Modification ignoree.\n";
                    }
                }

                std::cout << "Email [" << contact.getEmail() << "]: ";
                std::getline(std::cin, nouveauEmail);
                if (!nouveauEmail.empty()) {
                    if (validerEmail(nouveauEmail)) {
                        contact.setEmail(nouveauEmail);
                    } else {
                        std::cerr << "Email invalide. Modification ignoree.\n";
                    }
                }

                std::cout << "Contact modifie avec succes !\n";
                sauvegardeAutomatique();
                return;
            }
        }
        std::cout << "Aucun contact trouve avec l'ID : " << id << '\n';
    }

    // Supprimer un contact
    void supprimerContact(const std::string& id) {
        auto it = std::remove_if(contacts.begin(), contacts.end(),
                                 [&](const Contact& c) {
                                     return c.getId() == id;
                                 });
        if (it != contacts.end()) {
            contacts.erase(it, contacts.end());
            std::cout << "Contact supprime avec succes !\n";
            sauvegardeAutomatique();
        } else {
            std::cout << "Aucun contact trouve pour la suppression avec l'ID : " << id << '\n';
        }
    }

    // Sauvegarder dans un fichier
    void sauvegarder(const std::string& fichier) const {
        std::ofstream ofs(fichier);
        if (!ofs) {
            std::cerr << "Erreur lors de l'ouverture du fichier pour la sauvegarde.\n";
            return;
        }
        for (const auto& contact : contacts) {
            ofs << contact.serialiser();
        }
        ofs.close();
        std::cout << "Contacts sauvegardes avec succes dans " << fichier << '\n';
    }

    // Charger depuis un fichier
    void charger(const std::string& fichier) {
        std::ifstream ifs(fichier);
        if (!ifs) {
            std::cerr << "Aucun fichier trouve pour le chargement.\n";
            return;
        }
        contacts.clear();
        std::string ligne, id, nom, prenom, telephone, email;
        while (std::getline(ifs, ligne)) {
            std::istringstream ss(ligne);
            std::getline(ss, id, ';');
            std::getline(ss, nom, ';');
            std::getline(ss, prenom, ';');
            std::getline(ss, telephone, ';');
            std::getline(ss, email, ';');
            contacts.emplace_back(id, nom, prenom, telephone, email);
        }
        ifs.close();
        std::cout << "Contacts charges avec succes depuis " << fichier << '\n';
    }
};

#endif
