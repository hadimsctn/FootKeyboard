// src/contexts/SerialContext.js
import React, { createContext, useState } from "react";

export const SerialContext = createContext();

export const SerialProvider = ({ children }) => {
    const [port, setPort] = useState(null);
    const [output, setOutput] = useState("");
    const [receivedData, setReceivedData] = useState(""); // Dữ liệu nhận được từ Serial

  const connectToSerial = async () => {
    if ("serial" in navigator) {
      try {
        const selectedPort = await navigator.serial.requestPort();
        await selectedPort.open({ baudRate: 115200 });
        setPort(selectedPort);
        setOutput("Connected to serial device!");

        // Gửi tin nhắn ngay khi kết nối thành công
        await sendData("ALL=");

        // Đọc dữ liệu phản hồi sau khi gửi tin nhắn
        await readData(selectedPort);
      } catch (error) {
        console.error("Error connecting to serial port:", error);
        setOutput("Failed to connect to serial port.");
      }
    } else {
      setOutput("Web Serial API is not supported in your browser.");
    }
  };
  const sendData = async (message) => {
    if (true) {
      const encoder = new TextEncoderStream();
      const writableStreamClosed = encoder.readable.pipeTo(port.writable);
      const writer = encoder.writable.getWriter();
      await writer.write(message + "\n");
      writer.releaseLock();
      setOutput(`Sent: ${message}`);
    } else {
      console.error("No serial connection available.");
    }
  };

  const readData = async (port) => {
    if (port) {
      const decoder = new TextDecoderStream();
      const readableStreamClosed = port.readable.pipeTo(decoder.writable);
      const reader = decoder.readable.getReader();

      try {
        const { value, done } = await reader.read();
        if (done) {
          console.log("Stream closed.");
        }
        setReceivedData(value); // Lưu dữ liệu nhận được
        setOutput(`Received: ${value}`);
      } catch (error) {
        console.error("Error reading from serial port:", error);
      } finally {
        reader.releaseLock();
      }
    } else {
      console.error("No serial connection available.");
    }
  };

  return (
    <SerialContext.Provider
      value={{
        connectToSerial,
        sendData,
        receivedData,
        output,
        port, 
        setPort
      }}
    >
      {children}
    </SerialContext.Provider>
  );
};
