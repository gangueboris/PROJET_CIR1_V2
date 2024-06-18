// Exemple de données (peut être remplacé par des données réelles)
const data = {
    id: 1,
    firstName: "Rozanne",
    lastName: "Mccormick",
    father: {
        id: 2,
        firstName: "John",
        lastName: "Mccormick",
        father: {
            id: 4,
            firstName: "Robert",
            lastName: "Mccormick",
            father: null,
            mother: null
        },
        mother: {
            id: 5,
            firstName: "Anna",
            lastName: "Smith",
            father: null,
            mother: null
        }
    },
    mother: {
        id: 3,
        firstName: "Jane",
        lastName: "Doe",
        father: {
            id: 6,
            firstName: "William",
            lastName: "Doe",
            father: null,
            mother: null
        },
        mother: {
            id: 7,
            firstName: "Mary",
            lastName: "Johnson",
            father: null,
            mother: null
        }
    }
};

function createPersonElement(person, generation) {
    const personDiv = document.createElement("div");
    personDiv.className = `person generation-${generation}`;
    personDiv.innerHTML = `<h2>${person.firstName}, ${person.lastName}</h2>`;
    return personDiv;
}

function addGeneration(container, people, generation) {
    const generationDiv = document.createElement("div");
    generationDiv.className = `generation generation-${generation}`;
    
    people.forEach(person => {
        if (person) {
            const personElement = createPersonElement(person, generation);
            generationDiv.appendChild(personElement);
        }
    });

    container.appendChild(generationDiv);
}

function buildFamilyTree(data) {
    const treeContainer = document.getElementById("tree");
    const queue = [{ person: data, generation: 0 }];
    const generations = [];

    while (queue.length > 0) {
        const current = queue.shift();
        const person = current.person;
        const generation = current.generation;

        if (!generations[generation]) {
            generations[generation] = [];
        }

        generations[generation].push(person);

        if (person.father) {
            queue.push({ person: person.father, generation: generation + 1 });
        }
        if (person.mother) {
            queue.push({ person: person.mother, generation: generation + 1 });
        }
    }

    generations.forEach((generation, index) => {
        addGeneration(treeContainer, generation, index);
    });
}

document.addEventListener("DOMContentLoaded", () => {
    buildFamilyTree(data);
});
