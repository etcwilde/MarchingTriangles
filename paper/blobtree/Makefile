latexfile	= blobtree
figures		=

$(latexfile).pdf : $(figures) $(latexfile).tex references.bib
	rubber	--pdf $(latexfile)

clean:
	rubber	--clean $(latexfile)
	rm -f new.tex

proper:
	rubber	--clean $(latexfile)
	rm -f $(latexfile).synctex $(latexfile).synctex.gz $(latexfile).pdf
	rm -f $(latexfile).brf
	rm -f new.tex


diff.tex: old.tex new.tex
	latexdiff old.tex new.tex | perl -pe 's/^\\drafttrue//' > diff.tex

new.tex: $(latexfile).tex macros.tex
	latexpand --expand-bbl $(latexfile).bbl $(latexfile).tex > new.tex

diff.pdf: diff.tex
	pdflatex diff.tex

baseline:
	latexpand --expand-bbl $(latexfile).bbl $(latexfile).tex > old.tex
