all : clean rapport.pdf

rapport.pdf : rapport.tex
	pdflatex --shell-escape rapport.tex
	rm -f ./*.fls ./*.fdb_latexmk ./*.aux ./*.log ./*.lof ./*.out ./*.synctex.gz ./*.toc
	rm -rf ./_minted-rapport

clean :
	rm -rf rapport.pdf