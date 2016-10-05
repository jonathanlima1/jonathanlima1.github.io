var n, op, i, maior, cont = 0;

function iniciar(opcao){
	op = opcao;
	i = 1;

	document.getElementById("n").value = "";

	document.getElementById("ex").style.display="none";

	if(op == 1 || op == 2){		
		document.getElementById("n").value = (op == 1 ? 3 : 1000);

		receberN();
	}else{
		document.getElementById("recebern").style.display="block";
	}

}

function receberN(){
	n = document.getElementById("n").value;

	document.getElementById("recebern").style.display="none";
	document.getElementById("programa").style.display="block";
}

function receberValor(){
	valor = parseInt(document.getElementById("valor").value,10);

	if(valor != ""){
		if(i == 1){
			maior = valor;
		}else{
			if(valor > maior){
				maior = valor;
				cont = 1;
			}
			else
				if(valor == maior)
					cont++;
		}
		
		document.getElementById("valor").value = "";

		i++;

		if(i==n)
			document.getElementById("botao").value = "Finalizar";

		if(i > n){
			document.getElementById("programa").style.display="none";
			document.getElementById("resultado").style.display="block";

			mensagem = "O maior valor é "+maior+"!";

			if(op == 4 || op == 5)
				mensagem += " O número "+maior+" aparece "+cont+" vezes!";

			document.getElementById("mensagemResultado").innerHTML = mensagem;
		}else{
			document.getElementById("pergunta").innerHTML = "Digite o "+i+"º valor.";

			
		}
	}else{
		window.alert("Nenhum número encontrado. Insira o valor!");
	}
}