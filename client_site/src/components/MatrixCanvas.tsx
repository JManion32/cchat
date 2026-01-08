import { useEffect, useRef } from "react";
import { startMatrixEffect } from "../utils/matrixEffect";

/*===================================================
CREDIT TO:
Boujjou Achraf
https://codepen.io/wefiy/pen/WPpEwo
===================================================*/

export default function MatrixCanvas() {
  const canvasRef = useRef<HTMLCanvasElement>(null);

  useEffect(() => {
    if (!canvasRef.current) return;

    const stop = startMatrixEffect(canvasRef.current);
    return stop;
  }, []);

  return <canvas id="matrix-canvas" ref={canvasRef} />;
}
