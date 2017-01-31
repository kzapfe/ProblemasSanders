BIBLO=../../notasmixtas/TwoDiskBiblo.bib


*.pdf: 	$($(basename $@).tex) # $(BIBLO)
	pdflatex $< 
	bibtex $<
	pdflatex $<
	pdflatex $< 
	evince $@

