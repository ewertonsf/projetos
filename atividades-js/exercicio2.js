function atividadeJs() {
    nota_aluno = 6;

    if (nota_aluno >= 7){
        console.log("aprovado");
    } else if (nota_aluno >= 5 && nota_aluno < 7) {
        console.log("recuperação");
    } else {
        console.log("reprovado");
    }
}