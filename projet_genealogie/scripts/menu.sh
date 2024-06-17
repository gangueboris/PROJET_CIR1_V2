EXEC="./program"

# Compilation
make clean
make

# Boucle de menu
while true; do
    clear
    echo "===== Menu ============="
    echo "1. Rechercher la fratrie d'une personne par ID"
    echo "2. Rechercher toute la génération d'une personne par ID"
    echo "3. Rechercher les n premières personnes de la population par ID"
    echo "4. Rechercher la famille: NOM_DE_FAMILLE"
    echo "5. Compter le nombre de personnes qui ont le même prénom qu'une personne"
    echo "6. Quitter"
    echo "========================"
    read -p "Choisissez une option: " choice

    case $choice in
        1)
            read -p "Entrez l'ID de la personne: " id
            $EXEC fonction1 $id
            ;;
        2)
            read -p "Entrez l'ID de la personne: " id
            $EXEC fonction2 $id
            ;;
        3)
            read -p "Entrez le nombre de personnes: " n
            $EXEC fonction3 $n
            ;;
        4) 
            read -p "Entrez le nom de famille: " nom_de_famille
            $EXEC fonction4 $nom_de_famille
            ;;
        5)
            read -p "Entrez le prénom de la personne: " prenom
            $EXEC fonction5 $prenom
            ;;
        6)
            echo "Quitter..."
            break
            ;;
        *)
            echo "Option invalide. Veuillez réessayer."
            ;;
    esac
    read -p "Appuyez sur Entrée pour continuer..."
done