# sunnypilot Documentation

Source files for [docs.sunnypilot.ai](https://docs.sunnypilot.ai).

## Local Development

### Install dependencies

Install docs dependencies only - do **not** use `uv pip install .[docs]` as it will
reinstall the full sunnypilot package and break the development environment.

```bash
uv pip install Jinja2 mkdocs zensical
```

### Build

```bash
zensical build -f mkdocs-sp.yml
```

### Serve locally

```bash
zensical serve -f mkdocs-sp.yml
```

The site will be available at `http://127.0.0.1:8000`.

## Structure

- `docs_sp/` — Source markdown files
- `docs_site_sp/` — Build output (gitignored)
- `mkdocs-sp.yml` — Zensical configuration
