# sunnypilot Documentation

Source files for [docs.sunnypilot.ai](https://docs.sunnypilot.ai).

## Local Development

### Install dependencies

```bash
uv pip install ".[docs]"
```

### Build

```bash
zensical build
```

### Serve locally

```bash
zensical serve
```

The site will be available at `http://127.0.0.1:8000`.

## Structure

- `docs_sp/` — Source markdown files
- `docs_site_sp/` — Build output (gitignored)
- `zensical.toml` — Zensical configuration
