EXEC="./program"

if [ "$(uname -s)" = "Darwin" ]; then
    os_type=1
    open_command="open"
elif [ "$(uname -s)" = "Linux" ]; then
    os_type=2 
    open_command="xdg-open"
elif [[ "$(uname -s)" == CYGWIN* || "$(uname -s)" == MINGW* || "$(uname -s)" == MSYS* ]]; then
    os_type=3 
    open_command="start"
else
    os_type=0 
    echo "Système d'exploitation non supporté."
    exit 1
fi

make clean
make
./program

while true; do
    clear
    echo "===================================== Menu ====================================="
    echo "1. Générer toutes les n premières pages html"
    echo "2. Rechercher toute la génération d'une personne par ID"
    echo "3. Rechercher les frères et soeurs d'une personne par ID"
    echo "4. Quitter"
    echo "================================================================================"
    read -p "Choisissez une option: " choice

    case $choice in
        1)
            rm -f ../export/*.html
            read -p "Entrer un nombre n: " n
            $EXEC 1 $n
            echo "Page générée avec succès !"
            $open_command "../export/2-fiche.html"
            ;;  
        2)
            rm -f ../export/*.html
            read -p "Entrer l'ID de la personne: " id
            $EXEC 2 $id
            echo "Page générée avec succès !"
            $open_command "../export/$id-fiche.html"
            ;;
        3)
            rm -f ../export/*.html
            read -p "Entrer l'ID de la personne: " id
            echo "Page générée avec succès !"
            $EXEC 3 $id
            $open_command "../export/$id-fiche.html"
            ;;
        4)
            rm -f ../export/*.html
            echo "Quitter..."
            break
            ;;
        *)
            echo "Option invalide. Veuillez réessayer."
            ;;
    esac
    read -p "Appuyez sur Entrée pour continuer..."
done