#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <iostream>

class Contact {
private:
    std::string id;
    std::string nom;
    std::string prenom;
    std::string telephone;
    std::string email;

public:
    // Constructeur
    Contact(const std::string& id, const std::string& nom, const std::string& prenom, 
            const std::string& telephone, const std::string& email)
        : id(id), nom(nom), prenom(prenom), telephone(telephone), email(email) {}

    // Getters
    std::string getId() const { return id; }
    std::string getNom() const { return nom; }
    std::string getTelephone() const { return telephone; }
    std::string getPrenom() const { return prenom; } 
    std::string getEmail() const { return email; }  

    // Setters
    void setNom(const std::string& nouveauNom) { nom = nouveauNom; }
    void setPrenom(const std::string& nouveauPrenom) { prenom = nouveauPrenom; }
    void setTelephone(const std::string& nouveauTelephone) { telephone = nouveauTelephone; }
    void setEmail(const std::string& nouveauEmail) { email = nouveauEmail; }

    // Affichage
    void afficher() const {
        std::cout << "ID: " << id << ", Nom: " << nom << ", Prenom: " << prenom
                  << ", Telephone: " << telephone << ", Email: " << email << '\n';
    }

    // Sauvegarde
    std::string serialiser() const {
        return id + ";" + nom + ";" + prenom + ";" + telephone + ";" + email + "\n";
    }
};

#endif // CONTACT_H