document.addEventListener("DOMContentLoaded", () => {
    aplicarTemaSalvo();
    aplicarProgressoSalvo();

    document.getElementById("btnTema").addEventListener("click", alternarTema);
    document.getElementById("btnInstrucoes").addEventListener("click", toggleInstrucoes);
    document.getElementById("btnLimparProgresso").addEventListener("click", limparProgresso);
    document.getElementById("campoBusca").addEventListener("input", filtrarExercicios);
  });


  function aplicarTemaSalvo() {
    const salvo = localStorage.getItem("temaEscuro");
    const btn = document.getElementById("btnTema");
    if (salvo === "1") {
      document.body.classList.add("dark");
      btn.textContent = "☀️ Modo claro";
    } else {
      document.body.classList.remove("dark");
      btn.textContent = "🌙 Modo escuro";
    }
  }


  function alternarTema() {
    const btn = document.getElementById("btnTema");
    document.body.classList.toggle("dark");
    const escuroAtivo = document.body.classList.contains("dark");
    localStorage.setItem("temaEscuro", escuroAtivo ? "1" : "0");
    btn.textContent = escuroAtivo ? "☀️ Modo claro" : "🌙 Modo escuro";
  }


  function toggleInstrucoes() {
    const box = document.getElementById("boxInstrucoes");
    const btn = document.getElementById("btnInstrucoes");
    const visivel = box.style.display !== "none";
    box.style.display = visivel ? "none" : "block";
    btn.textContent = visivel ? "📌 Mostrar instruções" : "📌 Recolher instruções";
  }


  function aplicarProgressoSalvo() {
    const dados = JSON.parse(localStorage.getItem("exerciciosConcluidos") || "{}");
    document.querySelectorAll("li.exercicio").forEach(li => {
      const id = li.getAttribute("data-id");
      const concluido = dados[id];
      const btn = li.querySelector(".btn-mini");
      const label = li.querySelector(".status-label");
      if (concluido) {
        li.classList.add("concluido");
        if (btn) btn.textContent = "Concluído ✔";
        if (label) label.textContent = "Concluído";
      }
    });
    atualizarInfoBusca();
  }


  function toggleConcluido(botao, id) {
    const li = botao.closest("li.exercicio");
    const label = li.querySelector(".status-label");
    li.classList.toggle("concluido");

    const concluido = li.classList.contains("concluido");
    botao.textContent = concluido ? "Concluído ✔" : "Marcar como concluído";
    label.textContent = concluido ? "Concluído" : "";

    const dados = JSON.parse(localStorage.getItem("exerciciosConcluidos") || "{}");
    dados[id] = concluido;
    localStorage.setItem("exerciciosConcluidos", JSON.stringify(dados));

    atualizarInfoBusca();
  }


  function limparProgresso() {
    if (!confirm("Deseja realmente limpar o progresso salvo nesta máquina?")) return;
    localStorage.removeItem("exerciciosConcluidos");
    document.querySelectorAll("li.exercicio").forEach(li => {
      li.classList.remove("concluido");
      const btn = li.querySelector(".btn-mini");
      const label = li.querySelector(".status-label");
      if (btn) btn.textContent = "Marcar como concluído";
      if (label) label.textContent = "";
    });
    atualizarInfoBusca();
  }


  function filtrarExercicios() {
    const termo = document.getElementById("campoBusca").value.toLowerCase().trim();
    const exercicios = document.querySelectorAll("li.exercicio");
    let visiveis = 0;

    exercicios.forEach(li => {
      const texto = li.innerText.toLowerCase();
      if (!termo || texto.includes(termo)) {
        li.style.display = "";
        visiveis++;
      } else {
        li.style.display = "none";
      }
    });

    atualizarInfoBusca(visiveis);
  }

  
  function atualizarInfoBusca(qtdVisiveis = null) {
    const info = document.getElementById("infoBusca");
    const total = document.querySelectorAll("li.exercicio").length;
    if (qtdVisiveis === null) {
      // recálculo
      qtdVisiveis = 0;
      document.querySelectorAll("li.exercicio").forEach(li => {
        if (li.style.display !== "none") qtdVisiveis++;
      });
    }
    const concluidos = document.querySelectorAll("li.exercicio.concluido").length;
    info.textContent = `Mostrando ${qtdVisiveis} de ${total} exercícios. Concluídos: ${concluidos}.`;
  }
