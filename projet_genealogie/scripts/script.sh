# Definition de l'exécutable
EXEC="../src/output/program"

# Vérification du système d'exploitation sur lequel est exécuté le programme

if [ "$(uname -s)" = "Darwin" ]; then #  MacOs
    os_type=1
    open_command="open"
elif [ "$(uname -s)" = "Linux" ]; then # Linux
    os_type=2 
    open_command="xdg-open"
elif [[ "$(uname -s)" == CYGWIN* || "$(uname -s)" == MINGW* || "$(uname -s)" == MSYS* ]]; then # Windows
    os_type=3 
    open_command="start"
else
    os_type=0 
    echo "Système d'exploitation non supporté."
    exit 1
fi # Fin des conditions if

# Compilation du programme et excécution
# Changer de repertoire, exécuter le make et revenir dans le current répertoire
pushd ../src
make clean
make
popd


while true; do
    clear
    #echo "Current directory: $(pwd)" 
    echo "===================================== Menu ====================================="
    echo "1. Générer les ancêtres d'une personne par id"
    echo "2. Générer la fratrie d'une personne par id"
    echo "3. Afficher n personnes d'une ville"
    echo "4. Quitter"
    echo "================================================================================"
    read -p "Choisissez une option: " choice
    
    case $choice in
        1)
            rm -f ../export/*.html
            read -p "Entrer l'ID de la personne: " id
            $EXEC 1 $id
            echo "Pages générées avec succès !"
            $open_command "../export/$id-fiche.html"
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
            read -p "Enter un nombre n: " n
            read -p "Entrer le nom de la ville: " ville
            echo "Page générée avec succès !"
            $EXEC 3 "$n" "$ville"
            $open_command "../export/ville.html"
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