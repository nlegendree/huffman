all : rapport.pdf

rapport.pdf : rapport.tex
	pdflatex --shell-escape rapport.tex
	rm -f rapport.aux rapport.log rapport.toc
	rm -rf ./_minted-rapport

clean :
	rm -rf rapport.pdf