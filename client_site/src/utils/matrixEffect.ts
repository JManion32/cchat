// utils/matrixEffect.ts

/*===================================================
CREDIT TO:
Boujjou Achraf
https://codepen.io/wefiy/pen/WPpEwo
===================================================*/

export function startMatrixEffect(canvas: HTMLCanvasElement) {
  const ctx = canvas.getContext("2d");
  if (!ctx) return () => {};

  const chars =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789@#$%^&*()*&^%+-/~{[|`]}".split(
      ""
    );

  const fontSize = 10;
  let drops: number[] = [];
  let animationId = 0;
  const dropSpeed = 0.9;

  const resize = () => {
    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;

    const columns = Math.floor(canvas.width / fontSize);
    drops = Array(columns).fill(1);
  };

  resize();
  window.addEventListener("resize", resize);

  const draw = () => {
    ctx.fillStyle = "rgba(0, 0, 0, 0.04)";
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    ctx.fillStyle = "#009a22";
    ctx.font = `${fontSize}px monospace`;

    for (let i = 0; i < drops.length; i++) {
      const text = chars[Math.floor(Math.random() * chars.length)];
      ctx.fillText(text, i * fontSize, drops[i] * fontSize);

      if (
        drops[i] * fontSize > canvas.height &&
        Math.random() > 0.975
      ) {
        drops[i] = 0;
      }

      drops[i] += dropSpeed;
    }

    animationId = requestAnimationFrame(draw);
  };

  draw();

  // cleanup function
  return () => {
    cancelAnimationFrame(animationId);
    window.removeEventListener("resize", resize);
  };
}